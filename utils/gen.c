/*
 * This generates the filter / reduction code
 */

#include <stdio.h>
#include <stdlib.h>

char *myname;
int n_buffers;	// input buffers
int n_chan;	// input channels
int n_coef;	// number of coefficients.  Each used twice
int n_samp;	// number of samples in a buffer
int reduction;	// how much to reduce

char *buffer_prefix;
char *sample_prefix;
char *channel_prefix;
char *output_pointer_name;

static void
set_defaults()
{
	n_buffers = 3;
	n_chan = 6;
	n_coef = 8;
	n_samp = 16;
	reduction = 4;
	buffer_prefix = "adc_b";
	sample_prefix = "s";
	channel_prefix = "c";
	output_pointer_name = "output_pointer";
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
	if (n_samp < n_coef*2) {
		fprintf(stderr, "%s: n_samp(%d) < 2x n_coef(%d)\n",
				myname,
				n_samp,
				n_coef);
		errors++;
	}
	
	if (n_buffers < 3) {
		fprintf(stderr, "%s: n_buffers(%d) < 3\n",
				myname,
				n_buffers);
		errors++;
	}

	if (reduction < 1 || (n_samp / reduction) * reduction != n_samp) {
		fprintf(stderr, "%s: n_samp(%d) not a multiple of reduction(%d)\n",
				myname,
				n_samp,
				reduction);
		errors++;
	}

	if (errors)
		usage();
}

static void
access(int b1, int b2, int samp, int chan, int c)
{
	int b;
	int i;

	b = b1;
	if (c <= samp) {
		i = samp - c;
	} else {
		b = b2;
		i = n_samp - (c-samp);
	}
	printf("%s%d.%s%d.%s%d",
			buffer_prefix,
			b,
			sample_prefix,
			i,
			channel_prefix,
			chan);

}

// b1 is the current buffer, b2 is the prior buffer
static void
do_buf(int b1, int b2, int last)
{
	int samp;
	int chan;
	int c;

	printf("if (bf_desc == BFD_%d) {\n", b1);
	for (samp = 0; samp < n_samp; samp += reduction) {
		for (chan = 0; chan < n_chan; chan++) {
			printf("\t*%s++ = (uint16_t)((\n", output_pointer_name);
			for (c = 0; c < n_coef; c++) {
				printf("\tC%d * ((uint32_t)(", c);
				access(b1, b2, samp, chan, c);
				printf(" + ");
				access(b1, b2, samp, chan, 2 * n_coef - c - 1);
				if (c < n_coef - 1)
					printf(")) +\n");
				else
					printf(")) ) >> 16);\n");
			}
		}
	}
	if (last) {
		printf("}\n\n");
	} else {
		printf("} else ");
	}
}

int main(int argc, char **argv)
{
	int i;

	myname = *argv;

	grok_args(argc, argv);

	do_buf(0, n_buffers - 1, 0);
	for (i = 1; i < n_buffers; i++)
		do_buf(i, i-1, i == n_buffers - 1);
	return 0;
}
