// include the SD library:
#include <SPI.h>
#include <SD.h>

#define	MAX_BLOCKS 1

#define	NCHAN	6
#define	SAMPLES_PER_BLOCK	(21*4)

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

const int chipSelect = SDCARD_SS_PIN;
#define FILE_NAME "data.dat"

File dataFile;
int done;
int channel;
int sample;
int blocks;

struct header_s {
  uint32_t stime;	// as returned from "micros()"
  uint8_t  skipped;	// used to track how many buffers we skipped.
  uint8_t  d1;		// reserved for future use
  uint8_t  d2;		// reserved for future use
  uint8_t  d3;		// reserved for future use
  uint32_t d4;		// resereved for future use
  uint32_t d5;		// resereved for future use
};

struct block_s {
  struct header_s header;
  unsigned short samples[SAMPLES_PER_BLOCK][NCHAN];
} block;

void setup() {

  // Start the serial line
  Serial.begin(9600);
  while (!Serial) ;

  if (!SD.begin(chipSelect)) {
    Serial.println("SD initialization failed.");
    while (1);
  }
  Serial.println("SD Card up");

  dataFile = SD.open(FILE_NAME, FILE_READ);
  if (!dataFile) {
    Serial.println("Cannot open data file for reading");
    while (1);
  }
  done = 0;
  channel = NCHAN;
  sample = SAMPLES_PER_BLOCK - 1;
  blocks = 0;
}

void loop() {
  int n;

  if (!done) {
    if (channel >= NCHAN) {
      sample++;
      if (sample >= SAMPLES_PER_BLOCK) {
        if (blocks >= MAX_BLOCKS)
          goto finished;
        n = dataFile.read((char*)(&block), sizeof block);
        if (n != sizeof block)
          goto finished;
        blocks++;
        sample = 0;
      }
      channel = 0;
    }
    if (Serial.availableForWrite() > 16) {
      Serial.print(block.samples[sample][channel]);
      channel++;
      if (channel >= NCHAN)
        Serial.println("");
      else
        Serial.print(", ");
    }
  }
  return;

finished:
  Serial.println("Done");
  done = 1;
}
