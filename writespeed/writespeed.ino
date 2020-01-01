/*
  SD card test

  Measuring write speed to the SD card.

*/
// include the SD library:
#include <SPI.h>
#include <SD.h>

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

const int chipSelect = SDCARD_SS_PIN;
#define FILE_NAME "data.dat"

File dataFile;
long startTime;
long delta;

#define N_BUFFERS 1
#define N_WORDS (8*1024)

#define N_TO_WRITE  2048  // count is 0.5KB buffers

unsigned short buffers[N_BUFFERS][N_WORDS];

void setup() {
  short i, j;
  int n;
  short written;

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  if (!SD.begin(chipSelect)) {
    Serial.println("SD initialization failed.");
    while (1);
  }
  Serial.println("SD Card up");

  dataFile = SD.open(FILE_NAME, FILE_WRITE);
  if (!dataFile) {
    Serial.println("Cannot open data file for writing.");
    while (1);
  }

  // Put some non-zero stuff in the buffers
  for (i = 0; i < N_BUFFERS; i++) {
    buffers[i][0] = i;
    for (j = 1; j < N_WORDS; j++) {
      buffers[i][j] = j;
    }
  }

  startTime = millis();

  written = 0;

  while (1) {
    for (i = 0; i < N_BUFFERS; i++) {
      if (written >= N_TO_WRITE) {
        goto done;
      }
      n = dataFile.write((char*)(buffers[i]), 512);
      if (n != 512) {
        Serial.print("write returns ");
        Serial.println(n);
        goto done;
      }
      written++;
    }
  }
done:
  delta = millis() - startTime;
  Serial.print("Wrote ");
  Serial.print(written);
  Serial.print(" buffers in ");
  Serial.print(delta);
  Serial.println(" milliseconds");
}

void loop(void) {
}
