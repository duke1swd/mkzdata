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
char *ft_file_name;
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
FILE *ft_file;

int	cvalues[FILTER_SIZE_MAX + 1];

static void
set_defaults()
{
	n_buffers = 3;
	n_chan = 1;
	fw = 9;
	buffer_prefix = "adc_b";
	f1_prefix = "f1";
	f2_prefix = "f2";
	sample_prefix = "s";
	channel_prefix = "c";
	coefficient_prefix = "C";
	output_pointer_name = "output_pointer";
	word_type = "uint16_t";	// for mkrzero
	word_type = "int";	// for filter test
	header_file_name = "filter_defines.h";
	code_file_name = "filter_code.h";
	ft_file_name = "filter_test_code.h";
	fofs = 4.;
	wa0 = 0.5;
	wa1 = 0.5;
	verbose = 1;
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

	ft_file = fopen(ft_file_name, "w");
	if (ft_file == NULL) {
		fprintf(stderr, "%s: cannot open %s for writing\n",
				myname,
				ft_file_name);
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
	int c;
	int n_words;	// how much memory are we declaring?
	int words_per_sample;
	int words_per_buffer;
	int words_per_filter;

	n_words = 0;

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
	words_per_sample = n_chan;
	if (n_chan > 4)
		words_per_sample += 2;

	// Define an input buffer
	fprintf(header_file, "struct adc_block_s {\n");
	for (i = 0; i < n_samp; i++)
		fprintf(header_file, "\tstruct sample_s %s_%d;\n",
				sample_prefix,
				i);
	fprintf(header_file, "};\n\n");
	words_per_buffer = words_per_sample * n_samp;

	// Define an filter
	fprintf(header_file, "struct filter_s {\n");
	for (i = 0; i < n_coef * 2 - 1; i++)
		fprintf(header_file, "\t%s v%d;\n",
				word_type,
				i);
	fprintf(header_file, "};\n\n");
	words_per_filter = n_coef * 2 - 1;

	// Declare the input buffers
	for (i = 0; i < n_buffers; i++)
		fprintf(header_file, "struct adc_block_s adc_b%d;\n", i);
	fprintf(header_file, "\n");
	n_words += n_buffers * words_per_buffer;

	// Loop over all channels
	for (c = 0; c < n_chan; c++) {
		// Declare the first stage filters
		for (i = 0; i < n_f; i++)
			fprintf(header_file, "struct filter_s %s_%s_%d_%d;\n",
					f1_prefix,
					channel_prefix,
					c,
					i);
		fprintf(header_file, "\n");
		n_words += n_f * words_per_filter;

		// Declare the second stage filters
		for (i = 0; i < n_f; i++)
			fprintf(header_file, "struct filter_s %s_%s_%d_%d;\n",
					f2_prefix,
					channel_prefix,
					c,
					i);
		fprintf(header_file, "\n");
		n_words += n_f * words_per_filter;
	}

	if (verbose)
		printf("Declared %d words of storage\n", n_words);
}

static void
emit_storex(int stage, int f, int i, int c)
{
	// where does it go?
	fprintf(code_file, "\tf%d_%s_%d_%d.v%d = ",
			stage,
			channel_prefix,
			c,
			f,
			i);
}

static void
emit_store1(int f, int i, int c, int b, int s)
{
	// where does it go?
	emit_storex(1, f, i, c);
	// where does it come from?
	fprintf(code_file, "%s%d.%s_%d.%s_%d;\n",
			buffer_prefix,
			b,
			sample_prefix,
			s,
			channel_prefix,
			c);
}

static void
emit_store2(int f, int i, int c)
{
	// where does it go?
	emit_storex(2, f, i, c);
	// where does it come from?
	fprintf(code_file, "v;\n");
}

static void
emit_reference(int stage, int f, int i, int c)
{
	fprintf(code_file, "%s_%s_%d_%d.v%d",
			stage == 1? f1_prefix: f2_prefix,
			channel_prefix,
			c,
			f,
			i);
}


static void
do_buf(int b)
{
	int i;
	int s;	// current sample
	int c;	// current channel
	int f;	// current filter
	int fbase;

	for (c = 0; c < n_chan; c++)
		for (s = 0; s < n_samp; s++) {
			// this code copied from filtertest.c and modified as needed
			fbase = ((s+1)/2) % n_f;
			if (s % 2 == 0) {
				f = fbase;
				emit_store1(f, 0, c, b, s);
			} else {
				for (i = 0; i < n_f/2; i++) {
					f = (i + fbase) % n_f;
					emit_store1(f, i+1, c, b, s);
					f = (n_f  - 1 - i + fbase) % n_f;
					emit_store1(f, i+n_coef, c, b, s);
				}

				// Sum up filter 'f' and pass to the second stage
				fprintf(code_file, "\tv = (%s_0 * ",
						coefficient_prefix);
				emit_reference(1, f, 0, c);

				for (i = 1; i < n_coef; i++) {
					fprintf(code_file, " +\n\t\t");
					fprintf(code_file, "%s_%d * (",
							coefficient_prefix, i * 2 - 1);
					emit_reference(1, f, i, c);
					fprintf(code_file, " + ");
					emit_reference(1, f, i + n_coef - 1, c);
					fprintf(code_file, ")");
				}
				fprintf(code_file, ") >> 16;\n");

				// Handle the second stage filters here!
				i = (s-1)/2;
				fbase = (i/2) % n_f;
				if (i % 2 == 1) {
					f = fbase;
					emit_store2(f, 0, c);
				} else {
					for (i = 0; i < n_f/2; i++) {
						f = (i + fbase) % n_f;
						emit_store2(f, i+1, c);
						f = (n_f  - 1 - i + fbase) % n_f;
						emit_store2(f, i+n_coef, c);
					}

					// Sum up filter 'f' and spit it out
					fprintf(code_file, "\t*%s++ = (%s_0 * ",
							output_pointer_name,
							coefficient_prefix);
					emit_reference(2, f, 0, c);

					for (i = 1; i < n_coef; i++) {
						fprintf(code_file, " +\n\t\t");
						fprintf(code_file, "%s_%d * (",
								coefficient_prefix, i * 2 - 1);
						emit_reference(2, f, i, c);
						fprintf(code_file, " + ");
						emit_reference(2, f, i + n_coef - 1, c);
						fprintf(code_file, ")");
					}
					fprintf(code_file, ") >> 16;\n");
				}
			}
		}
}

static void
do_ftcode()
{
	int i;
	int buffer;

	fprintf(ft_file,
		"static void\n"
		"generated_filter()\n"
		"{\n"
		"\tint i;\n"
		"\tint buffer_selector;\n"
		"\t%s v;\n"
		"\t%s *%s;\n"
		"\n"
		"\tbuffer_selector = 0;\n"
		"\t%s = output[GENERATED_FILTER_OUTPUT];\n"
		"\tfor (i = 0; i <= sample_size - %d; ) {\n",
		word_type,
		word_type,
		output_pointer_name,
		output_pointer_name,
		n_samp);

	for (buffer = 0; buffer < n_buffers; buffer++) {
		fprintf(ft_file, "\t\t");
		if (buffer)
			fprintf(ft_file, "} else ");
		fprintf(ft_file, "if (buffer_selector == %d) {\n", buffer);
		for (i = 0; i < n_samp; i++)
			fprintf(ft_file, "\t\t\t%s%d.%s_%d.c_0 = samples[i++];\n",
					buffer_prefix,
					buffer,
					sample_prefix,
					i);
	}
	fprintf(ft_file, "\t\t}\n"
			"#include \"%s\"\n"
			"\t\tbuffer_selector += 1;\n"
			"\t\tif (buffer_selector >= %d)\n"
			"\t\t\tbuffer_selector = 0;\n"
			"\t}\n}\n",
			code_file_name,
			n_buffers);
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

	if (verbose) {
		printf("Generating code for filter width %d\n", fw);
		printf("\tNumber of channels = %d\n", n_chan);
		printf("\tNumber of samples per buffer = %d\n", n_samp);
	}

	gen_coefficients(cvalues, 0x10000, fofs, fw, wa0, wa1, 1.);
	do_headers();
	fclose(header_file);

	for (i = 0; i < n_buffers; i++) {
		if (i)
			fprintf(code_file, " else ");
		fprintf(code_file, "if (buffer_selector == %d) {\n", i);
		do_buf(i);
		fprintf(code_file, "}");
	}
	fprintf(code_file, "\n");
	fclose(code_file);

	do_ftcode();
	fclose(ft_file);

	return 0;
}
