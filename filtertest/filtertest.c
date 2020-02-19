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
#define TWOPI		(2. * 3.14159265359)
#define	FILTER_SIZE_MAX	65
#define	STAGE_FILTER_SIZE (FILTER_SIZE_MAX/2)
#define	N_OUTPUTS	4
#define	MAX_RESP_POINTS	1024

#define	SIMPLE_FILTER_OUTPUT	0
#define	SINGLE_PASS_OUTPUT	1
#define SINGLE_V2_OUTPUT	2
#define	GENERATED_FILTER_OUTPUT	3

char *filter_names[] = {
	"Simple",
	"Single v1",
	"Single v2",
	"Generated Filter",
	(char *)0,
};

enum input_types_e { noise, sqwave, snwave, file };

char *myname;
int filter_size;
int verbose;
int debug;
char *input_type_name;
enum input_types_e input_type;
int input_frequency;
double adc_frequency;
int sample_size;
char *input_file_name;
FILE *input_file;
double fofs;
double wa0;
double wa1;
double fresp_min, fresp_max;
int fresp_points;

int	cvalues[FILTER_SIZE_MAX];
int16_t	samples[MAX_SAMPLES];
int16_t	halfsamp[MAX_SAMPLES/2];
int16_t	output[N_OUTPUTS][MAX_SAMPLES/4+FILTER_SIZE_MAX];
int16_t	first_stage_filters[(FILTER_SIZE_MAX-1)/2][STAGE_FILTER_SIZE];
int16_t	second_stage_filters[(FILTER_SIZE_MAX-1)/2][STAGE_FILTER_SIZE];

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

#include "filter_defines.h"

static void
set_defaults()
{
	filter_size = GENERATED_FILTER_SIZE;
	fresp_min = 10.;
	fresp_max = 15000.;
	fresp_points = 0;
	input_type_name = "sqwave";
	input_frequency = 1000;
	adc_frequency = 35714.;
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
	fprintf(stderr, "\t-a <ADC frequency (%f)>\n", adc_frequency);
	fprintf(stderr, "\t-s <sample size (%d)>\n", sample_size);
	fprintf(stderr, "\t-t <signal type (");
	for (i_p = input_types; i_p->itype_name; i_p++) {
		if (i_p != input_types)
			fprintf(stderr, ", ");
		fprintf(stderr, "%s", i_p->itype_name);
	}
	fprintf(stderr, "To generate a response curve set number of points:\n");
	fprintf(stderr, "\t-n <number of points in curve (%d)\n", fresp_points);
	fprintf(stderr, "\t-M <minimum frequency in HZ (%.1f)\n", fresp_min);
	fprintf(stderr, "\t-X <maximum frequency in HZ (%.1f)\n", fresp_max);
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
	while ((c = getopt(argc, argv, "n:M:X:f:a:s:t:i:vdh")) != EOF)
		switch (c) {
			case 'f':
				filter_size = atoi(optarg);
				break;
			case 'a':
				adc_frequency = atof(optarg);
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
			case 'n':
				fresp_points = atoi(optarg);
				break;
			case 'M':
				fresp_min = atof(optarg);
				break;
			case 'X':
				fresp_max = atof(optarg);
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

	if (filter_size != GENERATED_FILTER_SIZE) {
		fprintf(stderr, "%s: Warning: Skipping generated filter.\n", myname);
		fprintf(stderr, "\tSet filter size (%d) to %d to enable\n",
				filter_size,
				GENERATED_FILTER_SIZE);
	}

	if (adc_frequency < 1) {
		fprintf(stderr, "%s: adc frequency (%f) must be positive\n",
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
		fprintf(stderr, "%s: adc frequency (%f) should not be "
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

	if (fresp_points < 0 || fresp_points >= MAX_RESP_POINTS) {
		fprintf(stderr, "%s: number of response points (%d) must be "
				"in the range [0-%d]\n",
				myname,
				fresp_points,
				MAX_RESP_POINTS);
		errors++;
	}

	if (fresp_min < 1. || fresp_min >= adc_frequency/4.) {
		fprintf(stderr, "%s: frequency response minimum (%f) must be in the "
				"range [1. - adc_frequency/4 (%f)]\n",
				myname,
				fresp_min,
				adc_frequency/4.);
		errors++;
	}

	if (fresp_max <= fresp_min || fresp_max >= adc_frequency/2.) {
		fprintf(stderr, "%s: frequency response maximum (%f) must be in the "
				"range [min resp freq (%f) - adc_frequency/2 (%f)]\n",
				myname,
				fresp_max,
				fresp_min,
				adc_frequency/2.);
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

/*
 * Simple filter with 2x down-sample
 */
static void
simple2x(int16_t *input, int16_t *output, int n)
{
	int i, j;
	int hw;
	long acc;

	hw = (filter_size - 1) / 2;
	if (debug > 1) 
		printf("\tfiltering %d samples with half-width %d\n",
				n, hw);

	for (i = hw; i < n - hw; i += 2) {
		acc = 0;
		for (j = -hw; j <= hw; j++)
			acc += (long)cvalues[j < 0? -j: j] * (long)input[i + j];
		*output++ = acc >> 16;
	}
}

static void
simple_filter()
{
	if (verbose) {
		printf("Running simple filter\n");
		fflush(stdout);
	}
	simple2x(samples, halfsamp, sample_size);
	simple2x(halfsamp, output[SIMPLE_FILTER_OUTPUT], (sample_size - filter_size)/2 + 1);
}

static int
single_pass_stage(int16_t filters[][STAGE_FILTER_SIZE],
	       	int index,
		int16_t sample)
{
	int i, f;
	int output;
	int fbase;
	int n_filters = (filter_size-1)/2;
	int n_coeff = (filter_size+3)/4;
	char *prefix;

	if (index == 1 && debug > 1)
		printf("n_filters = %d, n_coeff = %d\n", n_filters, n_coeff);

	// fbase rotates amongst the filters
	fbase = (index/2) % n_filters;
	if (debug > 1) {
		prefix = "";
		if (filters == second_stage_filters)
			prefix = "\t";
		printf("%sindex = %d, fbase = %d\n", prefix, index, fbase);
	}

	if (index % 2 == 0) {
		// Index is even
		for (i = 0; i < n_filters/2; i++) {
			f = (i + fbase) % n_filters;
			filters[f][i+1] = sample;
			if (debug > 1)
				printf("\t%sstoring in f[%d][%d]\n", prefix, f, i+1);
			f = (n_filters  - 1 - i + fbase) % n_filters;
			filters[f][i+1] = cvalues[i*2+1] *
				(sample + filters[f][i+1]);
			if (debug > 1)
				printf("\t%sa-m-s in f[%d][%d] with c[%d]\n", prefix, f, i+1, i*2+1);
		}
		output = 0;
		for (i = 0; i < n_coeff; i++)
			output += filters[f][i];
		if (debug > 1)
			printf("\t%soutput of %d from f[%d]\n", prefix, output >> 16, f);

		return output >> 16;
	} else {
		f = fbase;
		filters[f][0] = cvalues[0] * sample;
		if (debug > 1)
			printf("\t%sm-s in f[%d][0] with c[0]\n", prefix, f);
		return -1;
	}
}

static int
single_pass_stage_v2(int16_t filters[][STAGE_FILTER_SIZE],
	       	int index,
		int16_t sample)
{
	int i, f;
	int output;
	int fbase;
	int n_filters = (filter_size-1)/2;
	int n_coeff = (filter_size+3)/4;
	char *prefix;

	if (index == 1 && debug > 1)
		printf("n_filters = %d, n_coeff = %d\n", n_filters, n_coeff);

	// fbase rotates amongst the filters
	fbase = (index/2) % n_filters;
	if (debug > 1) {
		prefix = "";
		if (filters == second_stage_filters)
			prefix = "\t";
		printf("%sindex = %d, fbase = %d\n", prefix, index, fbase);
	}

	if (index % 2 == 0) {
		// Index is even
		for (i = 0; i < n_filters/2; i++) {
			f = (i + fbase) % n_filters;
			filters[f][i+1] = sample;
			if (debug > 1)
				printf("\t%sstoring %d in f[%d][%d]\n", prefix, sample, f, i+1);
			f = (n_filters  - 1 - i + fbase) % n_filters;
			filters[f][i+n_coeff] = sample;
			if (debug > 1)
				printf("\t%sstoring in f[%d][%d]\n", prefix, f, i+n_coeff);
		}
	} else {
		f = fbase;
		filters[f][0] = sample;
		if (debug > 1)
			printf("\t%sstoring in f[%d][0]\n", prefix, f);
		return -1;
	}

	// Sum up filter 'f' and spit it out
	if (debug > 1)
		printf("\t%soutputing filter f[%d] C_0(0)", prefix, f);
	output = filters[f][0] * cvalues[0];
	for (i = 1; i < n_coeff; i++) {
		output += cvalues[i * 2 - 1] * (filters[f][i] + filters[f][i + n_coeff-1]);
		if (debug > 1)
			printf(" C_%d(%d,%d)", i*2-1, i, i + n_coeff-1);
	}
	output >>= 16;
	if (debug > 1)
		printf(" => %d\n", output);

	return output;
}

static void
single_pass_filter(int (*stage)(int16_t f[][STAGE_FILTER_SIZE], int i, int16_t s), int f_n)
{
	int i;
	int val;
	int16_t *o_p;

	if (verbose) {
		printf("Running single pass filter\n");
		fflush(stdout);
	}

	// these memsets are not really needed.
	memset(first_stage_filters, 0, sizeof first_stage_filters);
	memset(second_stage_filters, 0, sizeof second_stage_filters);

	o_p = output[f_n];
	for (i = 0; i < sample_size; i++) {
		val = stage(first_stage_filters, i+1, samples[i]);
		if (i % 2 == 1) {
			val = stage(second_stage_filters, (i-1)/2, val);
			if (i % 4 == 1 && i >= 3*(filter_size-2)) {
				*o_p++ = val;
			}
		}
	}
}

#include "filter_test_code.h"

static void
call_generated_filter()
{
	int shift;

	generated_filter();
	// discard the first few output samples
	shift = (filter_size - 1)/2 + (filter_size - 1)/4 - 1;
	memmove(output[GENERATED_FILTER_OUTPUT], 
			output[GENERATED_FILTER_OUTPUT] + shift, 
			sizeof (int) * sample_size / 4);
}

/*
 * Compare two filter outputs.  Complain if they are different.
 */
static void
compare(int f1, int f2)
{
	int i;
	int first;
	int count;
	int outputs;
	int sum1, sum2;

	outputs = (sample_size - filter_size)/2 + 1;
	outputs = (outputs - filter_size)/2 + 1;
	printf("Comparing filters %s and %s on %d samples\n",
			filter_names[f1],
			filter_names[f2],
			outputs);
	if (outputs < 0)
		return;

	first = 1;
	count = 0;
	sum1 = sum2 = 0;
	for (i = 0; i < outputs; i++) {
		sum1 += output[f1][i];
		sum2 += output[f2][i];
		if (output[f1][i] != output[f2][i]) {
			count++;
			if (first) 
				printf("Filters %d and %d differ\n", f1, f2);

			if (first || verbose) 
				printf("\tsample %d, (%d != %d)\n",
					i,
					output[f1][i],
					output[f2][i]);
			first = 0;
		}
	}
	if (count == 0)
		printf("Filters match\n");
	else {
		printf("\t%d of %d samples do not match\n", count, outputs);
		printf("Averages are %.1f, %.1f\n",
				(double)sum1 / (double)outputs,
				(double)sum2 / (double)outputs);
	}
}

/*
 * This is the main execution flow.
 */
static void
doit()
{
	if (debug)
		printf("Filter width = %d\n", filter_size);

	// Create the filter coefficients
	gen_coefficients(cvalues, 0x10000, fofs, filter_size, wa0, wa1, 1.);

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
	if (filter_size % 4 == 1) {
		//single_pass_filter(single_pass_stage, SINGLE_PASS_OUTPUT);
		single_pass_filter(single_pass_stage_v2, SINGLE_V2_OUTPUT);
	}
	if (filter_size == GENERATED_FILTER_SIZE)
		call_generated_filter();

	//compare(SIMPLE_FILTER_OUTPUT, SINGLE_PASS_OUTPUT);
	//compare(SIMPLE_FILTER_OUTPUT, SINGLE_V2_OUTPUT);
	compare(SIMPLE_FILTER_OUTPUT, GENERATED_FILTER_OUTPUT);
}
