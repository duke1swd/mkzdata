/*
 * This program uses the serial port to talk to the arduino
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <sys/time.h>

#define	 BUF_SIZE	1280

char *myname;
char *device;
int debug;
int devicefd;
int nxfers;
int xfer;

static struct timeval st;

static void
start_time()
{
	int r;

	r = gettimeofday(&st, NULL);
	if (r < 0) {
		fprintf(stderr, "%s: Cannot get time of day\n",
				myname);
		perror("gettimeofday");
		exit(1);
	}
}

static void
end_time()
{
	int r;
	struct timeval et;
	double delta;

	r = gettimeofday(&et, NULL);
	if (r < 0) {
		fprintf(stderr, "%s: Cannot get time of day\n",
				myname);
		perror("gettimeofday");
		exit(1);
	}

	delta = et.tv_sec - st.tv_sec;
	delta += (double)(et.tv_usec - st.tv_usec)/1000000.;
	printf("Delta Time = %.3f\n", delta);
}

static int
readchar()
{
	char c;
	int n;

	for (;;) {
		n = read(devicefd, &c, 1);
		if (n <= 0)
			return -1;
		else if (n == 1)
			return c;
		else if (debug > 1)
			printf("got n=%d\n", n);
	}
}

/*
 * Read a new-line terminated string from the arduino
 */
static int
readline(char *lbuf, int n)
{
	int c;
	char *p;

	p = lbuf;
	for (;;) {
		c = readchar();
		if (c <= 0)
			return -1;
		if (debug)
			printf("Got %c (%o)\n", c, c);
		if (c == '\n') {
			*p = '\0';
			return 0;
		}
		if (n > 1) {
			n--;
			*p++ = c;
		}
	}
}

/*
 * This function attempts to talk to the arduino
 */
static int
doit()
{
	int i;
	int n;
	int cbl;
	char lbuf[BUF_SIZE];
	char cbuf[32];

	if (readline(lbuf, sizeof lbuf) < 0)
		return -1;

	if (debug)
		printf("Got from arduino: .%s.\n", lbuf);

	if (strcmp(lbuf, "HW") != 0) {
		fprintf(stderr, "%s: expected HW, got %s\n",
				myname,
				lbuf);
		return -1;
	}

	sprintf(cbuf, "s%d\n", xfer);
	cbl = strlen(cbuf);
	start_time();
	for (i = 0; i < nxfers; i++) {
		n = write(devicefd, cbuf, cbl);
		if (n != cbl) {
			fprintf(stderr, "%s: return on %d-byte write was %d\n",
					myname,
					cbl,
					n);
			return -1;
		}
		if (readline(lbuf, sizeof lbuf) < 0)
			return -1;

		if (debug)
			fprintf(stderr, "Got %ld bytes from arduino\n", strlen(lbuf));
	}
	end_time();
	printf("bytes = %d\n", nxfers * xfer);
	return 0;
}

static void conditiontty()
{
	int r;
	struct termios tty;

	r = tcgetattr(devicefd, &tty);
	if (r != 0) {
		fprintf(stderr, "%s: Cannot get modes on device %s\n",
				  myname,
				  device);
		perror("tcgetattr");
		exit(1);
	}
	cfmakeraw(&tty);
	r = tcsetattr(devicefd, TCSANOW, &tty);
	if (r != 0) {
		fprintf(stderr, "%s: Cannot set modes on device %s\n",
				  myname,
				  device);
		perror("tcsetattr");
		exit(1);
	}
}

static void
reopen()
{
	close(devicefd);

	for (;;) {
		devicefd = open(device, O_RDWR);
		if (devicefd >= 0) {
			conditiontty();
			return;
		}
		fprintf(stderr, "%s: Cannot open device %s for read/write\n",
				myname,
				device);
		sleep(1);
	}
}

static void
set_defaults()
{
	device = "/dev/ttyACM0";
	nxfers = 10;
	xfer = 1024;
	debug = 0;
}

static void
usage()
{
	set_defaults();
	fprintf(stderr, "Usage: %s <options>\n", myname);
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "\t-d <device (%s)>\n", device);
	fprintf(stderr, "\t-D (increase debugging)\n");
	fprintf(stderr, "\t-x <xfer size (%d)>\n", xfer);
	fprintf(stderr, "\t-n <number of transfers (%d)>\n", nxfers);
	exit(1);
}

static void
grok_args(int argc, char **argv)
{
	int c;
	int errors;
	int nargs;

	errors = 0;
	set_defaults();
	while ((c = getopt(argc, argv, "n:x:d:Dh")) != EOF)
		switch (c) {
			case 'n':
				nxfers = atoi(optarg);
				break;
			case 'x':
				xfer = atoi(optarg);
				break;
			case 'd':
				device = optarg;
				break;
			case 'D':
				debug++;
				break;
			default:
				usage();
		}

	if (nxfers < 1 || nxfers > 1000) {
		fprintf(stderr, "%s: number of transfers (%d) must be in the range [1-1000]\n",
				myname,
				nxfers);
		errors++;
	}

	if (xfer < 1 || xfer > BUF_SIZE - 2) {
		fprintf(stderr, "%s: xfer size (%d) must be in the range [1-%d]\n",
				myname,
				xfer,
				BUF_SIZE - 1);
		errors++;
	}

	nargs = argc - optind;
	if (nargs) {
		fprintf(stderr, "%s: no positional arguments are permitted\n",
				myname);
		errors++;
	}

	devicefd = open(device, O_RDWR);
	if (devicefd < 0) {
		fprintf(stderr, "%s: Cannot open device %s for read/write\n",
				myname,
				device);
		errors++;
	} else
		conditiontty();

	if (errors)
		usage();
}

int
main(int argc, char **argv)
{
	myname = *argv;
	grok_args(argc, argv);
	while (doit() < 0) 
		reopen();
	return 0;
}
