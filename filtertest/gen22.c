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
#include <string.h>

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

#define	OUTPUT_LINE_TYPE_STRING	1
#define	OUTPUT_LINE_TYPE_STORE	2
#define	OUTPUT_LINE_TYPE_GONE	3

struct output_lines_s {
	int type;
	struct output_lines_s *p_p;
	union {
		char *line;
		struct {
			char *from;
			char *to;
		} s;
	} u;
};

struct output_defines_s {
	int status;	// true if referenced.
	char *name;
};

int n_words;	// how much memory are we declaring?

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

/*
 * The output_lines routines are designed to optimize out unneeded load/stores
 * This implementation leaks memory rapidly.
 * And is horribly inefficient
 */
static char *
ds_copy(char *s)
{
	char *q;

	q = (char *)malloc(strlen(s)+1);
	if (q == (char *)0) {
		fprintf(stderr, "%s: malloc failed\n", myname);
		exit(1);
	}
	strcpy(q, s);
	return q;
}

static struct output_defines_s *output_defines_table;
int output_defines_table_length;
static struct output_lines_s *output_line_list;

static void
output_lines_init()
{
	output_line_list = (struct output_lines_s *)0;
}

static struct
output_lines_s *new_output_lines()
{
	struct output_lines_s *p;

	p = (struct output_lines_s *)malloc(sizeof (struct output_lines_s));
	if (p == (struct output_lines_s *)0) {
		fprintf(stderr, "%s: malloc failed\n", myname);
		exit(1);
	}
	p->type = OUTPUT_LINE_TYPE_GONE;
	p->p_p = output_line_list;
	output_line_list = p;
	return p;
}

static void
output_lines_string(char *s)
{
	struct output_lines_s *p;

	p = new_output_lines();
	p->type = OUTPUT_LINE_TYPE_STRING;
	p->u.line = ds_copy(s);
}

static void
output_lines_internal(struct output_lines_s *p)
{
	if (p) {
		output_lines_internal(p->p_p);
		switch (p->type) {
			case OUTPUT_LINE_TYPE_STRING:
				fprintf(code_file, "%s", p->u.line);
				break;
			case OUTPUT_LINE_TYPE_STORE:
				fprintf(code_file, "\t%s = %s;\n",
						p->u.s.to,
						p->u.s.from);
				break;
			default:
				break;
		}
	}
}

static void
output_lines()
{
	output_lines_internal(output_line_list);
}

static void
output_defines_init(int n)
{
	output_defines_table = (struct output_defines_s *)malloc(n * sizeof (struct output_defines_s));
	if (output_defines_table == (struct output_defines_s *)0) {
		fprintf(stderr, "%s: malloc failed\n", myname);
		exit(1);
	}
	memset(output_defines_table, 0, n * sizeof (struct output_defines_s));
	output_defines_table_length = n;
}

static void
output_defines_reference(char *s)
{
	int i;
	struct output_defines_s *p;

	for (p = output_defines_table, i = 0; i < output_defines_table_length; i++, p++)
		if (strcmp(s, p->name) == 0) {
			p->status = 1;
			return;
		}

	fprintf(stderr, "%s: reference to undefined temp variable %s\n",
			myname, s);
	exit(1);
}

static void
output_defines_print()
{
	int i;
	struct output_defines_s *p;

	for (p = output_defines_table, i = 0; i < output_defines_table_length; i++, p++)
		if (p->status) {
			fprintf(header_file, "static %s %s;\n",
					word_type,
					p->name);
			n_words++;
		}
}


static void
do_headers()
{
	int i;
	int j;
	int k;
	int stage;
	int c;
	int words_per_sample;
	int words_per_buffer;
	char lbuf[128];

	n_words = 0;

	fprintf(header_file, "#define GENERATED_FILTER_SIZE %d\n\n", fw);

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

	// Declare the input buffers
	for (i = 0; i < n_buffers; i++)
		fprintf(header_file, "static struct adc_block_s adc_b%d;\n", i);
	fprintf(header_file, "\n");
	n_words += n_buffers * words_per_buffer;

	// Loop over everything declaring the filter temp storage
	output_defines_init(n_chan * 2 * n_f * (n_coef * 2 - 1));
	k = 0;
	for (c = 0; c < n_chan; c++) {
		for (stage = 1; stage < 3; stage++)
			for (i = 0; i < n_f; i++)
				for (j = 0; j < n_coef * 2 - 1; j++) {
					sprintf(lbuf, "%s_%s_%d_%d_%s_%d",
							stage == 1? f1_prefix: f2_prefix,
							channel_prefix,
							c,
							i,
							"v",
							j);
					output_defines_table[k++].name = ds_copy(lbuf);
				}
	}
}

static void
emit_storex(int stage, int f, int i, int c)
{
	struct output_lines_s *p;
	char lbuf[128];

	// where does it go?
	sprintf(lbuf, "%s_%s_%d_%d_%s_%d",
			stage == 1? f1_prefix: f2_prefix,
			channel_prefix,
			c,
			f,
			"v",
			i);
	p = new_output_lines();
	p->type = OUTPUT_LINE_TYPE_STORE;
	p->u.s.to = ds_copy(lbuf);
	p->u.s.from = "";
}

static void
emit_store1(int f, int i, int c, int b, int s)
{
	char lbuf[128];

	// where does it go?
	emit_storex(1, f, i, c);
	// where does it come from?
	sprintf(lbuf, "%s%d.%s_%d.%s_%d",
			buffer_prefix,
			b,
			sample_prefix,
			s,
			channel_prefix,
			c);
	output_line_list->u.s.from = ds_copy(lbuf);
}

static void
emit_store2(int f, int i, int c)
{
	// where does it go?
	emit_storex(2, f, i, c);
	// where does it come from?
	output_line_list->u.s.from = "v";
}

static void
emit_reference(int stage, int f, int i, int c)
{
	struct output_lines_s *p;
	char lbuf[128];

	sprintf(lbuf, "%s_%s_%d_%d_%s_%d",
			stage == 1? f1_prefix: f2_prefix,
			channel_prefix,
			c,
			f,
			"v",
			i);
	if (debug > 1)
		printf("Searching for %s\n", lbuf);

	// Do we have a store up the stack for this reference?
	if (stage == 1)
		for (p = output_line_list; p; p = p->p_p) {
			if (p->type == OUTPUT_LINE_TYPE_STORE && debug > 1)
				printf("\t%s\n", p->u.s.to);
			if (p->type == OUTPUT_LINE_TYPE_STORE &&
					strcmp(lbuf, p->u.s.to) == 0) {
				// Yes, replace ref to filter temp with ref to buffer
				output_lines_string(p->u.s.from);
				// remove the store that used the filter temp
				p->type = OUTPUT_LINE_TYPE_GONE;
				if (debug > 1)
					printf("matched\n");
				return;
			}
		}

	// No matching store, pull the data from the filter temp
	output_defines_reference(lbuf);
	output_lines_string(lbuf);
}


static void
do_buf(int b)
{
	int i;
	int s;	// current sample
	int c;	// current channel
	int f;	// current filter
	int fbase;
	char lbuf[1024];

	for (c = 0; c < n_chan; c++) {
		output_lines_init();
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
				sprintf(lbuf, "\tv = (%s_0 * ",
						coefficient_prefix);
				output_lines_string(lbuf);
				emit_reference(1, f, 0, c);

				for (i = 1; i < n_coef; i++) {
					sprintf(lbuf, " +\n\t\t");
					output_lines_string(lbuf);
					sprintf(lbuf, "%s_%d * (",
							coefficient_prefix, i * 2 - 1);
					output_lines_string(lbuf);
					emit_reference(1, f, i, c);
					sprintf(lbuf, " + ");
					output_lines_string(lbuf);
					emit_reference(1, f, i + n_coef - 1, c);
					sprintf(lbuf, ")");
					output_lines_string(lbuf);
				}
				sprintf(lbuf, ") >> 16;\n");
				output_lines_string(lbuf);

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
						// optimize out the last store
						if (i < n_f/2-1)
							emit_store2(f, i+n_coef, c);
					}

					// Sum up filter 'f' and spit it out
					sprintf(lbuf, "\t*%s++ = (%s_0 * ",
							output_pointer_name,
							coefficient_prefix);
					output_lines_string(lbuf);
					emit_reference(2, f, 0, c);

					for (i = 1; i < n_coef; i++) {
						sprintf(lbuf, " +\n\t\t");
						output_lines_string(lbuf);
						sprintf(lbuf, "%s_%d * (",
								coefficient_prefix, i * 2 - 1);
						output_lines_string(lbuf);
						emit_reference(2, f, i, c);
						sprintf(lbuf, " + ");
						output_lines_string(lbuf);
						if (i == n_coef-1)
							// the last store was optimized out, but data is in 'v'
							output_lines_string("v");
						else
							emit_reference(2, f, i + n_coef - 1, c);
						sprintf(lbuf, ")");
						output_lines_string(lbuf);
					}
					sprintf(lbuf, ") >> 16;\n");
					output_lines_string(lbuf);
				}
			}
		}
		output_lines();
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

	for (i = 0; i < n_buffers; i++) {
		if (i)
			fprintf(code_file, " else ");
		fprintf(code_file, "if (buffer_selector == %d) {\n", i);
		do_buf(i);
		fprintf(code_file, "}");
	}
	fprintf(code_file, "\n");
	fclose(code_file);

	output_defines_print();

	if (verbose)
		printf("Declared %d words of storage\n", n_words);

	fclose(header_file);

	do_ftcode();
	fclose(ft_file);

	return 0;
}
