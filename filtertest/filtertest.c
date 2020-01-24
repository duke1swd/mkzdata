/*
 * Test various digital filter algorithms.
 * Notes:
 *   Filtersize is the number of input terms to the filter.
 *   Must be an odd number.  For some implementations only
 *   33 and 17 are legal values
 *
 *   Downsample can be any positive integer, but some implementions only support
 *   2 or 4
 *
 *   Input data can be one of these modes:
 *    * Random Noise
 *    * Square Wave
 *    * Sine Wave
 *    * Input file
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <math.h>

#define	MAX_SAMPLES	(1000*1000)
#define PI		3.14159265359
#define	FILTER_SIZE_MAX	65
#define	N_OUTPUTS	3

enum input_types_e { noise, sqwave, snwave, file };

char *myname;
int filter_size;
int verbose;
int debug;
char *input_type_name;
enum input_types_e input_type;
int input_frequency;
int adc_frequency;
int sample_size;
char *input_file_name;
FILE *input_file;
double fofs;
double wa0;
double wa1;

int	cvalues[FILTER_SIZE_MAX];
int	samples[MAX_SAMPLES];
int	halfsamp[MAX_SAMPLES/2];
int	output[N_OUTPUTS][MAX_SAMPLES/4];
int	first_stage_filters[(FILTER_SIZE_MAX-1)/2][(FILTER_SIZE_MAX-1)/4 + 1];
int	second_stage_filters[(FILTER_SIZE_MAX-1)/2][(FILTER_SIZE_MAX-1)/4 + 1];

struct input_type_s {
	enum input_types_e itype;
	char *itype_name;
} input_types[] = {
	{ noise, "noise"},
	{ sqwave, "sqwave"},
	{ snwave, "snwave"},
	{ file, "file"},
	{ 0, (char *)0 },
};

static void
set_defaults()
{
	filter_size = 17;
	input_type_name = "sqwave";
	input_frequency = 1000;
	adc_frequency = 35714;
	sample_size = 1000000;	// 1M
	input_type_name = input_types[0].itype_name;
	fofs = 4.;
	wa0 = 0.5;
	wa1 = 0.5;
	verbose = 0;
	debug = 0;
}

static void
usage()
{
	struct input_type_s *i_p;

	set_defaults();
	fprintf(stderr, "Usage: %s <options> [<input file>]\n", myname);
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "\t-f <filter size (%d)>\n", filter_size);
	fprintf(stderr, "\t-a <ADC frequency (%d)>\n", adc_frequency);
	fprintf(stderr, "\t-s <sample size (%d)>\n", sample_size);
	fprintf(stderr, "\t-t <signal type (");
	for (i_p = input_types; i_p->itype_name; i_p++) {
		if (i_p != input_types)
			fprintf(stderr, ", ");
		fprintf(stderr, "%s", i_p->itype_name);
	}
	fprintf(stderr, ")\n");
	fprintf(stderr, "\t-i <input frequency (%d)>\n", input_frequency);
	fprintf(stderr, "\t-v (increase verbosity)\n");
	fprintf(stderr, "\t-d (increase debugging)\n");
	exit(1);
}

static void
grok_args(int argc, char **argv)
{
	int c;
	int errors;
	int nargs;
	int input_frequency_set;
	struct input_type_s *i_p;

	errors = 0;
	input_frequency_set = 0;
	set_defaults();
	while ((c = getopt(argc, argv, "f:a:s:t:i:vdh")) != EOF)
		switch (c) {
			case 'f':
				filter_size = atoi(optarg);
				break;
			case 'a':
				adc_frequency = atoi(optarg);
				break;
			case 's':
				sample_size = atoi(optarg);
				break;
			case 't':
				input_type_name = optarg;
				break;
			case 'i':
				input_frequency = atoi(optarg);
				input_frequency_set++;
				break;
			case 'v':
				verbose++;
				break;
			case 'd':
				debug++;
				break;
			default:
				usage();
		}

	if (debug && !verbose)
		verbose++;

	for (i_p = input_types; i_p->itype_name; i_p++)
		if (strcmp(input_type_name, i_p->itype_name) == 0)
			goto i_found;
	fprintf(stderr, "%s: input type (%s) is not understood\n",
			myname,
			input_type_name);
	errors++;
i_found:
	input_type = i_p->itype;

	if (filter_size < 3 || filter_size > FILTER_SIZE_MAX) {
		fprintf(stderr, "%s: filter size (%d) must be in the range [3-%d]\n",
				myname,
				filter_size,
				FILTER_SIZE_MAX);
		errors++;
	}  else if (filter_size % 2 != 1) {
		fprintf(stderr, "%s: filter size (%d) must be an odd number\n",
				myname,
				filter_size);
		errors++;
	}

	if (filter_size % 4 != 1) {
		fprintf(stderr, "%s: Warning: Skipping single pass filter.\n", myname);
		fprintf(stderr, "\tSet filter size (%d) to 1 more than a multiple of 4 to enable\n",
				filter_size);
	}

	if (adc_frequency < 1) {
		fprintf(stderr, "%s: adc frequency (%d) must be positive\n",
				myname,
				adc_frequency);
		errors++;
	}

	if (input_frequency < 1) {
		fprintf(stderr, "%s: input frequency (%d) must be positive\n",
				myname,
				input_frequency);
		errors++;
	}

	if (adc_frequency < input_frequency) {
		fprintf(stderr, "%s: adc frequency (%d) should not be "
				"smaller than input_frequency (%d)\n",
				myname,
				adc_frequency,
				input_frequency);
		errors++;
	}

	if (sample_size < 1 || sample_size > MAX_SAMPLES) {
		fprintf(stderr, "%s: sample size (%d) must be in the range [1 - %d]\n",
				myname,
				sample_size,
				MAX_SAMPLES);
		errors++;
	}

	nargs = argc - optind;

	if (nargs && input_type != file) {
		fprintf(stderr, "%s: positional arguments only used when input type (%s) is \"file\"\n",
				myname,
				input_type_name);
		errors++;
	}

	if (nargs != 1 && input_type == file) {
		fprintf(stderr, "%s: input type \"file\" requires exactly 1 postional argument\n",
				myname);
		errors++;
	}

	if (nargs) {
		input_file_name = argv[optind];
		input_file = fopen(input_file_name, "r");
		if (input_file == NULL) {
			fprintf(stderr, "%s: cannot open file %s for reading\n",
					myname,
					input_file_name);
			errors++;
		}
	} else
		input_file_name = "";

	if (input_frequency_set && input_type == file)
		fprintf(stderr, "%s: Warning: input frequency (%d) ignore for input type \"file\"\n",
				myname,
				input_frequency);

	if (errors)
		usage();
}

static void doit();

int
main(int argc, char **argv)
{
	myname = *argv;
	grok_args(argc, argv);
	doit();
	return 0;
}

static void
get_file_samples()
{
}

static void
gen_noise_samples()
{
	int i;

	for (i = 0; i < sample_size; i++)
		samples[i] = (0xfff & (rand() / 17));
}

static void
gen_square_samples()
{
}

static void
gen_sine_samples()
{
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
	double sinc;
	double window;

	if (n == 0)
		return 1.;

	sinc = sin((double)(2 * n) * PI / (double) foverfs) / (2. * PI * (double) n / (double) foverfs);
	window = windowa0 + windowa1 * cos((double)(2 * n) * PI / (double)N);
	return sinc * window;
}

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
	for (i = 0; i < N; i++)
		sum += gen_coef((N-1)/2 - i, foverfs, N, windowa0, windowa1);

	for (i = 0; i < N; i++)
		coefficients[i] = (int)(gen_coef((N-1)/2 - i, foverfs, N, windowa0, windowa1) *
			gain / sum * scaleone);
}

/*
 * Simple filter with 2x down-sample
 */
static void
simple2x(int *input, int *output, int n)
{
	int i, j, x;
	int hw;
	long acc;

	hw = (filter_size - 1) / 2;

	for (i = 0; i < n; i += 2) {
		acc = 0;
		for (j = -hw; j <= hw; j++) {
			x = i + j;
			if (x >= 0 && x < n)
				acc += (long)cvalues[j + hw] * (long)input[x];
		}
		*output++ = acc;
	}
}

#define	SIMPLE_FILTER_OUTPUT	0
#define	SINGLE_PASS_OUTPUT	1
static void
simple_filter()
{
	if (verbose) {
		printf("Running simple filter\n");
		fflush(stdout);
	}
	simple2x(samples, halfsamp, sample_size);
	simple2x(halfsamp, output[SIMPLE_FILTER_OUTPUT], sample_size/2);
}

static int
single_pass_stage(int filters[][(FILTER_SIZE_MAX-1)/4 + 1],
	       	int index,
		int sample)
{
	int i, f;
	int output;
	int fbase;
	int n_filters = (filter_size-1)/2;
	int n_coeff = (filter_size+3)/4;

	if (index == 0 && debug > 1)
		printf("n_filters = %d, n_coeff = %d\n", n_filters, n_coeff);

	// fbase rotates amongst the filters
	fbase = (index/2) % n_filters;
	if (debug > 1)
		printf("index = %d, fbase = %d\n", index, fbase);

	if (index % 2 == 0) {
		// Index is even
		for (i = 0; i < n_filters/2; i++) {
			f = (i+ n_filters - 1 + fbase) % n_filters;
			filters[f][i+1] = sample;
			if (debug > 1)
				printf("\tstoring in f[%d][%d]\n", f, i+1);
			f = (n_filters - 2 - i + fbase) % n_filters;
			filters[f][i+1] = cvalues[i*2+1] *
				(sample + filters[f][i+1]);
			if (debug > 1)
				printf("\ta-m-s in f[%d][%d] with c[%d]\n", f, i+1, i*2+1);
		}
		output = 0;
		if (debug > 1)
			printf("\toutput from f[%d]\n", f);
		for (i = 0; i < n_coeff; i++)
			output += filters[f][i];

		return output;
	} else {
		f = (index/2 + n_filters/2 + 1) % n_filters;
		filters[f][0] = cvalues[0] * sample;
		if (debug > 1)
			printf("\tm-s in f[%d][0] with c[0]\n", f);
		return -1;
	}
}

static void
single_pass_filter()
{
	int i;
	int val;
	int *o_p;

	if (verbose) {
		printf("Running single pass filter\n");
		fflush(stdout);
	}
	o_p = output[SINGLE_PASS_OUTPUT];
	for (i = 0; i < sample_size; i++) {
		val = single_pass_stage(first_stage_filters, i, samples[i]);
		/*xxx*/val = -1;
		if (val >= 0) {
			val = single_pass_stage(second_stage_filters, i/2, val);
			if (val >= 0)
				*o_p++ = val;
		}
	}
}

/*
 * This is the main execution flow.
 */
static void
doit()
{
	// Create the filter coefficients
	gen_coefficients(cvalues, 0x10000, fofs, filter_size, wa0, wa1, 4.);

	// Get the input data.
	switch (input_type) {
		case file:
			get_file_samples();
			break;
		case noise:
			gen_noise_samples();
			break;
		case sqwave:
			gen_square_samples();
			break;
		case snwave:
			gen_sine_samples();
			break;
	}

	simple_filter();
	if (filter_size % 4 == 1)
		single_pass_filter();
}
