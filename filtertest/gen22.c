/*
 * This generates code fragments used for a 2 stage filter.
 * Each filter stage is identical, and downsamples 2x.
 * With 2 stages you get 4x downsampling.
 *
 * There are two output files.  One defines the data structures,
 * the second is the code to take a buffer of input samples and
 * generate 1/4 that many output samples.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TWOPI		(2. * 3.14159265359)
#define	FILTER_SIZE_MAX	65

char *myname;
int n_buffers;	// input buffers.  Need at least 3, I think
int n_chan;	// input channels.  Plan is 6 ADC channels
int fw;		// nominal filter width.  Needs to be 5, 9, or 13

char *buffer_prefix;
char *f1_prefix;
char *f2_prefix;
char *sample_prefix;
char *channel_prefix;
char *coefficient_prefix;
char *output_pointer_name;
char *word_type;	// all input, output and intermediates are this type
char *header_file_name;
char *code_file_name;
double fofs;
double wa0;
double wa1;

int verbose;
int debug;

// these values are computed from the filter width
int n_coef;	// number of coefficients.  Each used twice
int n_f;	// number of filters in each stage
int n_samp;	// number of samples in a buffer

FILE *header_file;
FILE *code_file;

int	cvalues[FILTER_SIZE_MAX + 1];

static void
set_defaults()
{
	n_buffers = 3;
	n_chan = 6;
	fw = 9;
	buffer_prefix = "adc_b";
	f1_prefix = "f1";
	f2_prefix = "f2";
	sample_prefix = "s";
	channel_prefix = "c";
	coefficient_prefix = "C";
	output_pointer_name = "output_pointer";
	word_type = "unsigned short";
	header_file_name = "filter_defines.h";
	code_file_name = "filter_code.h";
	fofs = 4.;
	wa0 = 0.5;
	wa1 = 0.5;
	verbose = 0;
	debug = 0;
}

static void
usage()
{
	exit(1);
}

static void
grok_args(int argc, char **argv)
{
	int errors;
	set_defaults();

	errors = 0;

	if (fw < 5 || fw > FILTER_SIZE_MAX) {
		fprintf(stderr, "%s: filter width must be in the range [5-%d]\n",
				myname,
				FILTER_SIZE_MAX);
		errors++;
	} else if (fw % 4 != 1) {
		fprintf(stderr, "%s: filter width (%d) module 4 != 1\n",
				myname,
				fw);
		errors++;
	}

	if (n_buffers < 3) {
		fprintf(stderr, "%s: n_buffers(%d) < 3\n",
				myname,
				n_buffers);
		errors++;
	}

	header_file = fopen(header_file_name, "w");
	if (header_file == NULL) {
		fprintf(stderr, "%s: cannot open %s for writing\n",
				myname,
				header_file_name);
		perror("open");
		errors++;
	}

	code_file = fopen(code_file_name, "w");
	if (code_file == NULL) {
		fprintf(stderr, "%s: cannot open %s for writing\n",
				myname,
				code_file_name);
		perror("open");
		errors++;
	}

	if (errors)
		usage();
}

/*
 * Generate a single filter coefficient.
 * These are unnormalized floating point numbers
 * n runs the range -(N-1)/2 to +(N-1)/2
 */
double
gen_coef(int n,
		double foverfs,
		int N,
		double windowa0,
		double windowa1)
{
	double v;
	double sinc;
	double window;

	if (n == 0)
		return 1.;

	v = TWOPI * (double)n / foverfs;
	sinc = sin(v) / v;
	window = windowa0 + windowa1 * cos(TWOPI * (double)(n) / (double)N);
	return sinc * window;
}

/*
 * Generate the vector of filter coefficients
 */
static void gen_coefficients(int *coefficients,
		int scaleone,
		double foverfs,
		int N,
		double windowa0,
		double windowa1,
		double gain)
{
	int i;
	double sum;

	// Sum up the unnormalized coefficients
	sum = 0;
	for (i = 0; i <= (N-1)/2; i++)
		sum += gen_coef(i, foverfs, N, windowa0, windowa1);
	sum = sum * 2 - gen_coef(0, foverfs, N, windowa0, windowa1);

	// Normalize the sum to 1.0 * gain, then scale and truncate to integer
	for (i = 0; i <= (N-1)/2; i++)
		coefficients[i] = (int)(gen_coef(i, foverfs, N, windowa0, windowa1) *
			gain / sum * scaleone);

	if (debug > 1) {
		printf("\nCoefficients:\n");
		for (i = 0; i <= (N-1)/2; i++)
			printf("\t%2d %.5f %4d\n",
					i,
					(double)coefficients[i] / (double)0x10000,
					coefficients[i]);
	}
}

// emit the data structure definitions and the constants
static void
print_constant(int n, int v)
{
	fprintf(header_file,
			"#define %s_%d %d\n",
			coefficient_prefix,
			n,
			v);
}

static void
do_headers()
{
	int i;

	fprintf(header_file, "// Filter Size = %d\n\n", fw);

	// Define the filter coefficients
	print_constant(0, cvalues[0]);
	for (i = 1; i <= (n_coef-1) * 2 - 1; i += 2)
	       print_constant(i, cvalues[i]);	
	fprintf(header_file, "\n");

	// Define an input sample
	fprintf(header_file, "struct sample_s {\n");
	for (i = 0; i < n_chan; i++) {
		if (i == 4)
			fprintf(header_file, "\t%s null_0;\n"
					"\t%s null_1;\n",
					word_type,
					word_type);
		fprintf(header_file, "\t%s %s_%d;\n",
				word_type,
				channel_prefix,
				i);
	}
	fprintf(header_file, "};\n\n");

	// Define an input buffer
	fprintf(header_file, "struct adc_block_s {\n");
	for (i = 0; i < n_samp; i++)
		fprintf(header_file, "\tstruct sample_s %s_%d;\n",
				sample_prefix,
				i);
	fprintf(header_file, "};\n\n");

	// Declare the input buffers
	for (i = 0; i < n_buffers; i++)
		fprintf(header_file, "struct adc_block_s adc_b%d;\n", i);
	fprintf(header_file, "\n");
}

// b1 is the current buffer, b2 is the prior buffer
static void
do_buf(int b1, int b2, int last)
{
}

int main(int argc, char **argv)
{
	int i;

	myname = *argv;

	grok_args(argc, argv);

	// some basic math
	n_f = (fw - 1) / 2;
	n_coef = (fw + 3) / 4; // omit coefficients that are zero.  Count only the unique ones.
	n_samp = n_f * 4;

	gen_coefficients(cvalues, 0x10000, fofs, fw, wa0, wa1, 1.);
	do_headers();
	fclose(header_file);

	do_buf(0, n_buffers - 1, 0);
	for (i = 1; i < n_buffers; i++)
		do_buf(i, i-1, i == n_buffers - 1);
	return 0;
}
