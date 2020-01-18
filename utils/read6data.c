/*
 * Give a data file writen by adcsd3, create a CSV file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// block header
struct header_s {
  unsigned long stime;	// as returned from "micros()"
  unsigned char skipped;	// used to track how many buffers we skipped.
  unsigned char d1;		// reserved for future use
  unsigned char d2;		// reserved for future use
  unsigned char d3;		// reserved for future use
  unsigned long d4;		// resereved for future use
  unsigned long d5;		// resereved for future use
};

#define	NCHAN	6
#define	SAMPLES_PER_BLOCK	(21*4)

struct block_s {
	struct header_s header;
	unsigned short samples[SAMPLES_PER_BLOCK][NCHAN];
} block;

static void
doit(int fd, FILE *output)
{
	int n;
	int s, c;

	while ((n = read(fd, (void *)&block, sizeof block)) == sizeof block)
		for (s = 0; s < SAMPLES_PER_BLOCK; s++) {
			for (c = 0; c < NCHAN; c++) {
				if (c)
					printf(", ");
				printf("%6d", block.samples[s][c]);
			}
			printf("\n");
		}
}

int
main(int argc, char **argv)
{
	int ifd;
	FILE *output;

	ifd = 0;
	output = stdout;

	doit(ifd, output);
	return 0;
}
