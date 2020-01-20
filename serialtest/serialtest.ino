char *iptr;
int icnt;
char lbuf[1280];
int mode;

#define	SENDING	1
#define	LISTENING 2

static void readytoread() {
  iptr = lbuf;
  icnt = 0;
  mode = LISTENING;
}

/*
   returns TRUE if we've just read a complete input line (NL terminated)
*/
static int readline() {
  int c;
  if (Serial.available() < 1)
    return 0;

  c = Serial.read();
  if (c < 0)
    return 0;

  if (c == '\n') {
    *iptr = '\0';
    return 1;
  }

  if (icnt < sizeof lbuf - 1) {
    *iptr++ = c;
    icnt++;
  }
  return 0;
}

/*
   Set up a string to be written
*/
static void writestring(char *s) {
  strncpy(lbuf, s, sizeof lbuf - 1);
  lbuf[sizeof lbuf - 1] = '\0';
  iptr = lbuf;
  mode = SENDING;
}

/*
   processing writing the buffer.
   Returns true on buffer empty
*/
static int writeline() {
  if (*iptr == '\0')
    return 1;
  if (Serial.availableForWrite() >= 1)
    Serial.write(*iptr++);
  return 0;
}

/*
   Process commands sent from the host
*/

/*
   The 's' command takes a numeric argument -- how many bytes
   to send back to the host.  Plus one more, the '\n'.
   truncated to fit into the lbuf
*/
static void sendcmd() {
  char *p;
  int n;

  while (*iptr == ' ')
    iptr++;

  n = atoi(iptr);
  if (n <= 0)
    return;

  if (n >= sizeof lbuf - 1)
    n = sizeof lbuf - 2;

  for (p = lbuf; n-- > 0; )
    *p++ = 'x';
  *p++ = '\n';
  *p = '\0';
  iptr = lbuf;
  mode = SENDING;
}

static void command() {
  char c;
  char *p;

  iptr = lbuf;
  switch (c = *iptr++) {
    case 's':
      sendcmd();
      break;
    default:
      writestring("unknown command ");
      p = lbuf + strlen(lbuf);
      *p++ = c;
      *p++ = '\n';
      *p = '\0';
      break;
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  delay(1000);  // wait a bit
  writestring("HW\n");
}

void loop() {
  if (mode == SENDING)
    if (writeline())
      readytoread();
  if (mode == LISTENING)
    if (readline())
      command();
}
