/*
   This program reads from the ADC and writes to the SD card.

   Goal is to run the ADC_CLK at 2.0MHz, sample 8 channels
   2 of which are not connected, filter and downsample the
   remaining 6, generating 8929 output samples/sec/channel,
   which we write to the SD card.
   These are written in a packed 12-bit format.
   Output data rate is about 107,000 bytes/sec

   The analog data is filtered and down-sampled 4x.  The down-sampling
   is done in 2 stages, and the data is filtered each time.  The two
   filter stages use identical coefficients.

   The filters are convolved and unrolled for maximum efficiency.  The
   code to define and impement the filters is created by gen22.c and
   included here.

   Each sample is 12 bits, stored in a 16-bit word, right justified.

   Because of the way the pins are laid out and connected in order to get
   the adc sampling feature to scan 6 pins we need to scan 2 pins that
   are not connected.  The values from those pins are loaded into memory
   but never used.  See the definition of struct sample_s in filter_defines.h

   The term "block" in this code usually means the amount of data we get
   per DMA complete interrupt.
*/

#define IL_LOGGING 1
#undef IL_LOGGING

#define	DURATION	(30ul * 1000000ul)	// in microseconds

// include the SD library:
#include <SPI.h>
#include <SD.h>

#include "filter_defines.h"

// Each output block has a header.
struct header_s {
  uint32_t stime;	// as returned from "micros()"
  uint8_t  skipped;	// used to track how many buffers we skipped.
  uint8_t  d1;		// reserved for future use
  uint8_t  d2;		// reserved for future use
  uint8_t  d3;		// reserved for future use
  uint32_t d4;		// resereved for future use
  uint32_t d5;		// resereved for future use
};

/*
   Notes on skipped buffers:
   We are attempting to output approximate 140K bytes/second.
   Since each output buffer is 1024 bytes, that is about 280 buffers/second.
   If we skip more than 256 buffers, we'll lose track of how many we skipped,
   but that is about a second, which should never happen.
*/


#define	HEADER_SIZE		(sizeof (struct header_s) / sizeof (uint16_t))
#define	N_OUTPUT_BUFFERS	16
#define	OUTPUT_BUFFER_SIZE	512	// in 16-bit words
#define	OUTPUTS_PER_BLOCK	(GENERATED_SAMPLES_PER_BLOCK * GENERATED_CHANNELS / 4)
#define	ADC_BLOCKS_PER_BUFFER	((OUTPUT_BUFFER_SIZE - HEADER_SIZE) / OUTPUTS_PER_BLOCK)

volatile uint8_t buffer_status[N_OUTPUT_BUFFERS];
#define	EMPTY 		0
#define	FILLING		1
#define	FULL		2
#define	EMPTYING	3
uint16_t buffers[N_OUTPUT_BUFFERS][OUTPUT_BUFFER_SIZE];
uint16_t *output_pointer;	// not volatile because, except for first init, only used in ISR
int output_counter;
int current_buffer;
int reduce_errors;
int dump_buffer;
volatile int total_skipped;

#define ADCPIN0 A3		// A3 _must_ be the base pin.  Others are not consecutive.
#define ADCPIN1 A4
#define ADCPIN2 A5
#define ADCPIN3 A6
#define ADCPIN4 A1
#define ADCPIN5 A2
#define NPINS 8
#define	N_DMA_CHANNELS 1		// This is the number of DMA channels we use.  There are 12, but we don't use them all.
#define	MY_GENERIC_CLOCK 4u

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

const int chipSelect = SDCARD_SS_PIN;
#define FILE_NAME "data.dat"

File dataFile;

int buffers_written;
int buffers_filled;

// Interrupt logging stuff
#ifdef IL_LOGGING
#define	IL_MAX	16
uint32_t il_times[IL_MAX];
uint8_t il_reasons[IL_MAX];

#define	IL_START	0x8
#define	IL_TDONE	0x2
#define	IL_TERR		0x1
#define	IL_SUSP		0x4
uint16_t il_overflow;
uint8_t il_count;
#endif

// This structure is defined in section 20.10
typedef struct {
  uint16_t btctrl;
  uint16_t btcnt;
  uint32_t srcaddr;
  uint32_t dstaddr;
  uint32_t descaddr;
} dmacdescriptor ;

volatile dmacdescriptor wrb[N_DMA_CHANNELS] __attribute__ ((aligned (16)));	// this is a region in memory where the descriptors will be written back.
dmacdescriptor descriptor_section[N_DMA_CHANNELS] __attribute__ ((aligned (16)));// the source descriptors
dmacdescriptor descriptor __attribute__ ((aligned (16)));		// a single descriptor used temp
dmacdescriptor descriptor2 __attribute__ ((aligned (16)));		// a single descriptor used as for the second ADC buffer
dmacdescriptor descriptor3 __attribute__ ((aligned (16)));		// a single descriptor used as for the third ADC buffer

#define	BFD_2	((uint32_t)(&adc_b0) + sizeof adc_b0)
#define	BFD_0	((uint32_t)(&adc_b1) + sizeof adc_b1)
#define	BFD_1	((uint32_t)(&adc_b2) + sizeof adc_b2)

/*
   Debugging print routine.
*/
void print_buffer(volatile struct adc_block_s *p) {
  int i;
  uint16_t *q;

  q = (uint16_t *)p;

  for (i = 0; i < sizeof (struct adc_block_s) / (sizeof (uint16_t)); i++) {
    if (i % NPINS == 0)
      Serial.println("");
    Serial.print("  ");
    Serial.print(q[i]);
  }
}

/*
   Set up the buffer we are about to write to.
*/
void init_buffer() {
  uint32_t t;
  struct header_s *h_p;

  output_pointer = buffers[current_buffer];

  // Set up the buffer header
  h_p = (struct header_s *)output_pointer;
  t = micros();
  //h_p->stime = t;

  // If we are re-using a buffer, bump the skip count, else reset it to zero.
  if (buffer_status[current_buffer] == FILLING) {
    if (h_p->skipped < 255) {
      h_p->skipped += 1;

    }
    total_skipped += 1;
  } else
    h_p->skipped = 0;

  h_p->d1 = 0;
  h_p->d2 = 0;
  h_p->d3 = 0;
  h_p->d4 = 0;
  h_p->d5 = 0;
  output_pointer += HEADER_SIZE;

  buffer_status[current_buffer] = FILLING;

  // how many more samples can we put in this buffer?
  output_counter = ADC_BLOCKS_PER_BUFFER;
}

static uint32_t chnl = 0;  // DMA channel
volatile uint32_t dmadone;
volatile uint32_t cpu_c;

/*
   This is the DMA controller interrupt handler.
   THis definition overrides the definition in the arduino core libraries.
   We handle these interrupts
 	DMAC_CHINTENCLR_TERR		transfer error
 	DMAC_CHINTENCLR_TCMPL		transfer complete
 	DMAC_CHINTENCLR_SUSP		DMA suspended
*/
void DMAC_Handler() {
  int i;
  int v;
  int next_buffer;
  uint32_t bf_desc;
  int buffer_selector;

  // interrupts DMAC_CHINTENCLR_TERR DMAC_CHINTENCLR_TCMPL DMAC_CHINTENCLR_SUSP
  // These are transfer error, transfer complete, and DMA suspended
  uint8_t active_channel;

  // disable irqs ?  Not sure why this is necessary.  Perhaps to prevent recursive calls?
  __disable_irq();
  active_channel =  DMAC->INTPEND.reg & DMAC_INTPEND_ID_Msk; // get channel number
  DMAC->CHID.reg = DMAC_CHID_ID(active_channel);
  dmadone = DMAC->CHINTFLAG.reg;	// huh?

#ifdef IL_LOGGING
  il_times[il_count] = micros();
  il_reasons[il_count] = (dmadone & 0x7);
#endif

  DMAC->CHINTFLAG.reg = DMAC_CHINTENCLR_TCMPL; // clear
  DMAC->CHINTFLAG.reg = DMAC_CHINTENCLR_TERR;
  DMAC->CHINTFLAG.reg = DMAC_CHINTENCLR_SUSP;

  // which descriptor are we using?
  bf_desc = wrb[0].dstaddr;

  // which descriptor are we using?
  bf_desc = wrb[0].dstaddr;
  buffer_selector = 99;
  if (bf_desc == BFD_0)
    buffer_selector = 0;
  else if (bf_desc == BFD_1)
    buffer_selector = 1;
  else if (bf_desc == BFD_2)
    buffer_selector = 2;

  // Filter the input buffers into the output buffers
#if 1
#include "filter_code.h"
  else reduce_errors++;
#endif

  if (--output_counter <= 0) {
    buffers_filled++;
    next_buffer = current_buffer + 1;
    if (next_buffer >= N_OUTPUT_BUFFERS) {
      next_buffer = 0;
    }

    if (buffer_status[next_buffer] == EMPTY) {
      buffer_status[current_buffer] = FULL;
      current_buffer = next_buffer;
    }
    init_buffer();
  }

#ifdef IL_LOGGING
  if (il_count >= IL_MAX - 1) {
    il_overflow++;
  } else {
    il_count++;
  }
#endif
  __enable_irq();

}


// PM stands for Power Manager.  See chapter 16
// Note that APB is the standard ARM peripheral bus, while AHB is the standard ARM high-performance bus.
// THhere is one AHB that is sync'd to the CPU core, and three) APBs (a thru c) that are async, and go through
// an AHB to APB bus bridge.
// Note that the burst length is hardwired to 1 beat.
void dma_init() {
#ifdef IL_LOGGING
  il_overflow = 0;
  il_count = 1;
  il_reasons[0] = IL_START;
#endif
  // probably on by default
  // The DMAC controller requires both an AHB and an APB clock to be up and running.  See 20.5.3
  PM->AHBMASK.reg |= PM_AHBMASK_DMAC ;
  PM->APBBMASK.reg |= PM_APBBMASK_DMAC ;
  NVIC_EnableIRQ( DMAC_IRQn ) ;

  DMAC->BASEADDR.reg = (uint32_t)descriptor_section;
  DMAC->WRBADDR.reg = (uint32_t)wrb;
  DMAC->CTRL.reg = DMAC_CTRL_DMAENABLE | DMAC_CTRL_LVLEN(0xf);	// this enables the DMAC and all 4 of its arbitration levels
}

/*
   This routine turns on the ADC and kicks off the DMA of the ADC.
*/
void adc_dma() {
  uint32_t temp_CHCTRLB_reg;
  int i, j;

  DMAC->CHID.reg = DMAC_CHID_ID(chnl);		// hard wired in this code to channel 0.
  DMAC->CHCTRLA.reg &= ~DMAC_CHCTRLA_ENABLE;	// Disable the channel
  DMAC->CHCTRLA.reg = DMAC_CHCTRLA_SWRST;	// Reset the channel.  Return to defaults
  // I think this logic clears the trigger for this channel, while doing nothing to the other channels.
  DMAC->SWTRIGCTRL.reg &= (uint32_t)(~(1 << chnl)); // according to 20.8, writing a 1 will trigger the channel
  // set the CHCTRLB register to:
  //	level 0 (highest?)
  //	source is ADC_DMAC_ID_RESRDY: an ADC result is ready.  See page 350
  //	action is BEAT, do one beat.
  temp_CHCTRLB_reg = DMAC_CHCTRLB_LVL(0) |
                     DMAC_CHCTRLB_TRIGSRC(ADC_DMAC_ID_RESRDY) | DMAC_CHCTRLB_TRIGACT_BEAT;
  DMAC->CHCTRLB.reg = temp_CHCTRLB_reg;
  DMAC->CHINTENSET.reg = DMAC_CHINTENSET_MASK ; // enable all 3 interrupts
  dmadone = 0;

  // set up the first of 3 descriptors, one for each adc buffer
  // link to second descriptor
  descriptor.descaddr = (uint32_t)&descriptor2;
  descriptor.srcaddr = (uint32_t) &ADC->RESULT.reg;
  descriptor.btcnt =  (uint16_t)(sizeof adc_b0) / 2;
  // why is the dstaddr set to beyond the end of the buffer?
  // Book says, "address corresponding to the last beat transfer address in the block transfer"
  descriptor.dstaddr = (uint32_t)(&adc_b0) + sizeof adc_b0; // end address
  // the beat size is a half-word (16 bits), we increment the destination, and the descriptor is valid.
  // Note that we do not set a step size, nor a source increment
  // block action is interrupt -- we'll get a transfer complete interrupt on every block.
  descriptor.btctrl =  DMAC_BTCTRL_BEATSIZE_HWORD | DMAC_BTCTRL_DSTINC | DMAC_BTCTRL_VALID | DMAC_BTCTRL_BLOCKACT_INT;
  // Put the descriptor where it goes.  Not sure why we didn't just initialize in place.
  memcpy(&descriptor_section[chnl], &descriptor, sizeof(dmacdescriptor));

  // set up the second of 3
  descriptor2.descaddr = (uint32_t)&descriptor3;
  descriptor2.srcaddr = (uint32_t) &ADC->RESULT.reg;
  descriptor2.btcnt =  (uint16_t)(sizeof adc_b1) / 2;
  descriptor2.dstaddr = (uint32_t)(&adc_b1) + sizeof adc_b1; // end address
  descriptor2.btctrl =  DMAC_BTCTRL_BEATSIZE_HWORD | DMAC_BTCTRL_DSTINC | DMAC_BTCTRL_VALID | DMAC_BTCTRL_BLOCKACT_INT;
  // third descriptor, back to the first
  descriptor3.descaddr = (uint32_t)descriptor_section;
  descriptor3.srcaddr = (uint32_t) &ADC->RESULT.reg;
  descriptor3.btcnt =  (uint16_t)(sizeof adc_b2) / 2;
  descriptor3.dstaddr = (uint32_t)(&adc_b2) + sizeof adc_b2; // end address
  descriptor3.btctrl =  DMAC_BTCTRL_BEATSIZE_HWORD | DMAC_BTCTRL_DSTINC | DMAC_BTCTRL_VALID | DMAC_BTCTRL_BLOCKACT_INT;

  // Set up the output buffers
  for (i = 0; i < N_OUTPUT_BUFFERS; i++) {
    buffer_status[i] = EMPTY;
    for (j = 0; j < OUTPUT_BUFFER_SIZE; j++) {
      buffers[i][j] = 0;
    }
  }
  current_buffer = 0;
  reduce_errors = 0;
  init_buffer();

  // start channel
#ifdef IL_LOGGING
  il_times[0] = micros();
#endif
  DMAC->CHID.reg = DMAC_CHID_ID(chnl);
  DMAC->CHCTRLA.reg |= DMAC_CHCTRLA_ENABLE;

  // Start the ADC running.
  adc_start();
}

// turn off DMA by breaking the infinite loop of dma descriptors.
// then wait what I hope is long enough.
void dma_off() {
  descriptor3.descaddr = 0;
  delay(10);
}

// Not sure this routine is needed.
static __inline__ void ADCsync() __attribute__((always_inline, unused));
static void   ADCsync() {
  while (ADC->STATUS.bit.SYNCBUSY == 1); //Just wait till the ADC is free
}

/*
   This code sets up generic clock #4 to run at 8.0MHz
*/
void gclk4() {
  GCLK->GENDIV.reg = GCLK_GENDIV_ID(MY_GENERIC_CLOCK) |	// Generic Clock Generator 4
                     GCLK_GENDIV_DIV(6);		// divide the clock by 6 to generate 8 MHz.

  while (GCLK->STATUS.bit.SYNCBUSY == 1); // Wait for synchronization

  /* Write Generic Clock Generator 4 configuration */
  GCLK->GENCTRL.reg = GCLK_GENCTRL_ID( MY_GENERIC_CLOCK ) | // Generic Clock Generator 4
                      GCLK_GENCTRL_SRC_DFLL48M | // Selected source is DFLL 48MHz
                      GCLK_GENCTRL_IDC | // Set 50/50 duty cycle
                      GCLK_GENCTRL_GENEN ;
  while (GCLK->STATUS.bit.SYNCBUSY == 1); // Wait for synchronization

  /* Route this clock to the ADC_CLK */
  GCLK->CLKCTRL.reg = (uint16_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN(MY_GENERIC_CLOCK) | GCLK_CLKCTRL_ID_ADC);
  while ( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY ) ; // Wait for synchronization
}


void adc_init() {
  uint32_t itemp;
  analogRead(ADCPIN0);  // do some pin init  pinPeripheral()
  analogRead(ADCPIN1);  // do some pin init  pinPeripheral()
  analogRead(ADCPIN2);  // do some pin init  pinPeripheral()
  analogRead(ADCPIN3);  // do some pin init  pinPeripheral()
  analogRead(ADCPIN4);  // do some pin init  pinPeripheral()
  analogRead(ADCPIN5);  // do some pin init  pinPeripheral()
  ADC->CTRLA.bit.ENABLE = 0x00;             // Disable ADC
  ADCsync();

  // Set the reference to Vdd / 2.  I believe Vdd is 3.3V.
  ADC->REFCTRL.bit.REFSEL = ADC_REFCTRL_REFSEL_INTVCC1_Val;
  ADC->INPUTCTRL.bit.GAIN = ADC_INPUTCTRL_GAIN_1X_Val;
  ADCsync();    //  ref 31.6.16
  // first pin to scan
  itemp = g_APinDescription[ADCPIN0].ulADCChannelNumber << ADC_INPUTCTRL_MUXPOS_Pos;
  // Scan the pins
  itemp |= ADC_INPUTCTRL_INPUTSCAN(NPINS - 1);
  // set the gain
  itemp |= ADC_INPUTCTRL_GAIN_1X;
  // set the INPUTRCTRL register
  ADC->INPUTCTRL.reg = itemp;
  ADCsync();
  ADC->AVGCTRL.reg = 0x00 ;       //no averaging
  ADC->SAMPCTRL.reg = 0x00;  ; //sample length in 1/2 CLK_ADC cycles
  ADCsync();

  // The input clock is 8MHz.  We scale by 4x to get 2.0 MHz.  Max allowed is 2.1MHz,
  // but I don't see an easy way to generate that.
  ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV4 | ADC_CTRLB_FREERUN | ADC_CTRLB_RESSEL_12BIT;
  ADCsync();
}

void adc_start() {
  ADC->CTRLA.bit.ENABLE = 0x01;
  ADCsync();
}


/*
   Timer Management Code Here
   The timer is used to drive the control loop at 500Hz
*/
#define CTRL_TC         TC5
#define CTRL_TC_IRQn    TC5_IRQn
#define CTRL_TC_TOP     0xFFFF
#define CTRL_TC_CHANNEL 0
#define	CTRL_CC_VAL	24000	// ticks at 12 MHz, so 500 Hz

#define WAIT_TC16_REGS_SYNC(x) while(x->COUNT16.STATUS.bit.SYNCBUSY);

static inline void resetTC (Tc* TCx)
{
  // Disable TCx
  TCx->COUNT16.CTRLA.reg &= ~TC_CTRLA_ENABLE;
  WAIT_TC16_REGS_SYNC(TCx)

  // Reset TCx
  TCx->COUNT16.CTRLA.reg = TC_CTRLA_SWRST;
  WAIT_TC16_REGS_SYNC(TCx)
  while (TCx->COUNT16.CTRLA.bit.SWRST);
}

/*
   Interrupt priorities:
   I believe that DMA is on 0 (high), USB is on 0 (high) and systick is on 2 (low).
   So this should put us below DMAC (good), below USB (OK, I guess), and above systick (ok)
*/
#define CTRL_TC_NVIC_PRIORITY ((1<<__NVIC_PRIO_BITS) - 1)

void start_control_loop()
{
  // Configure interrupt request
  NVIC_DisableIRQ(CTRL_TC_IRQn);
  NVIC_ClearPendingIRQ(CTRL_TC_IRQn);

  NVIC_SetPriority (CTRL_TC_IRQn, CTRL_TC_NVIC_PRIORITY);  /* set Priority */

  // Enable GCLK for TC4 and TC5 (timer counter input clock)
  GCLK->CLKCTRL.reg = (uint16_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID(GCM_TC4_TC5));
  while (GCLK->STATUS.bit.SYNCBUSY);

  resetTC(CTRL_TC);

  uint16_t tmpReg = 0;
  tmpReg |= TC_CTRLA_MODE_COUNT16;  // Set Timer counter Mode to 16 bits
  tmpReg |= TC_CTRLA_WAVEGEN_MFRQ;  // Set CTRL_TC mode as match frequency
  tmpReg |= TC_CTRLA_PRESCALER_DIV4;// Set Prescaler to 4x == 12 MHz
  CTRL_TC->COUNT16.CTRLA.reg |= tmpReg;
  WAIT_TC16_REGS_SYNC(CTRL_TC)

  CTRL_TC->COUNT16.CC[CTRL_TC_CHANNEL].reg = (uint16_t) CTRL_CC_VAL;
  WAIT_TC16_REGS_SYNC(CTRL_TC)

  // Enable the CTRL_TC interrupt request
  CTRL_TC->COUNT16.INTENSET.bit.MC0 = 1;

  // Enable CTRL_TC
  CTRL_TC->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;
  WAIT_TC16_REGS_SYNC(CTRL_TC)

  NVIC_EnableIRQ(CTRL_TC_IRQn);
}

static void myLoop();

#ifdef __cplusplus
extern "C" {
#endif

// TC5 ISR
void TC5_Handler (void)
{

  // Clear the interrupt
  CTRL_TC->COUNT16.INTFLAG.bit.MC0 = 1;
  myLoop();
}

#ifdef __cplusplus
}
#endif



#ifdef IL_LOGGING
void il_dump() {
  int i, local_count;

  local_count = il_count;
  if (il_overflow) {
    local_count++;
  }
  Serial.print("count: ");
  Serial.println(local_count);
  if (local_count > IL_MAX) {
    local_count = IL_MAX;
  }

  for (i = 0; i < local_count; i++) {
    Serial.print(il_times[i] - il_times[0]);
    Serial.print(": ");
    if (il_reasons[i] & IL_START) {
      Serial.print("start ");
    }
    if (il_reasons[i] & IL_TDONE) {
      Serial.print("done ");
    }
    if (il_reasons[i] & IL_TERR	) {
      Serial.print("error ");
    }
    if (il_reasons[i] & IL_SUSP) {
      Serial.print("suspend ");
    }
    if (il_reasons[i] & 0x40) {
      Serial.print("B0");
    }
    if (il_reasons[i] & 0x80) {
      Serial.print("B1");
    }
    Serial.println("");
  }
  if (il_overflow) {
    Serial.print("Overflows: ");
    Serial.println(il_overflow);
  }
}
#endif

// Setup the output path.
// Basically this means initializing things
// and opening the output file.
void output_setup()
{
  if (!SD.begin(chipSelect)) {
    Serial.println("SD initialization failed.");
    while (1);
  }
  Serial.println("SD Card up");

  if (!SD.remove(FILE_NAME)) {
    Serial.println("could not remove file");
  }

  dataFile = SD.open(FILE_NAME, FILE_WRITE);
  if (!dataFile) {
    Serial.println("Cannot open data file for writing.");
    while (1);
  }
  if (!dataFile.seek(0ul)) {
    Serial.println("Seek failed.");
    while (1);
  }
  dump_buffer = 0;
  total_skipped = 0;
  buffers_written = 0;
  buffers_filled = 0;
}

// CPU measurement code
void measure(char *name) {
  uint32_t t1, t2, i;

#if 1
  t1 = micros();
#else
  t1 = 0;
#endif
  for (i = 0; i < 1000000; i++) {
    cpu_c += 1;
    cpu_c += 1;
  }
#if 1
  t2 = micros();
#else
  t2 = 1;
#endif
  Serial.println(name);
  Serial.print("  ");
  Serial.println(t2 - t1);
}

uint32_t start_time;
uint32_t end_time;
int errors;
int printed;
int delta_max;

#define DIVIDE_VAL	100
#define LED_PIN LED_BUILTIN
int divider;
int led_val;
volatile uint32_t count_clicks;

void setup() {
  Serial.begin(9600);
  while (!Serial) ;
  Serial.println("Hello World");
  measure("idle cpu");

  gclk4();
  Serial.println("GCLK 4 set up");
  adc_init();
  Serial.println("adc_init complete");
  dma_init();
  Serial.println("dma_init complete");
  output_setup();
  Serial.println("output_setup complete");
  divider = 0;
  count_clicks = 0;
  pinMode(LED_PIN, OUTPUT);
  start_control_loop();
  Serial.println("control loop started");
  errors = 0;
  adc_dma();
  start_time = micros();
  end_time = start_time + DURATION;
  printed = 0;
  delta_max = 0;
}

/*
   This code dumps the data buffers to disk.
*/
int tbs;
void loop() {
  int n;
  uint32_t now;
  uint32_t delta;

  now = micros();
  if (now <= end_time && buffer_status[dump_buffer] == FULL) {
    buffer_status[dump_buffer] = EMPTYING;
    tbs = total_skipped; // Note that total_skipped is volatile and may continue to increment after this point.
#if 1
    n = dataFile.write((char*)(buffers[dump_buffer]), OUTPUT_BUFFER_SIZE * sizeof (uint16_t));
#else
    n = OUTPUT_BUFFER_SIZE * sizeof (uint16_t);
#endif
    buffer_status[dump_buffer] = EMPTY;
    if (n != OUTPUT_BUFFER_SIZE * sizeof (uint16_t)) {
      errors += 1;
    }
    dump_buffer += 1;
    if (dump_buffer >= N_OUTPUT_BUFFERS)
      dump_buffer = 0;
    buffers_written += 1;
  }
  if (now >= end_time && !printed) {
    dma_off();
    dataFile.close();
    printed++;
    Serial.println("Done");
    Serial.print("FIlter width: ");
    Serial.println(GENERATED_FILTER_SIZE);
    Serial.print("Buffers written: ");
    Serial.println(buffers_written);
    Serial.print("Buffers filled: ");
    Serial.println(buffers_filled);
    Serial.print("Total Skips: ");
    Serial.println(tbs);
    Serial.print("Total Errors: ");
    Serial.println(errors);
    Serial.print("Total Time (sec): ");
    Serial.println((double)(now - start_time) / 1000000.);
    Serial.print("Blocks per buffer: ");
    Serial.println(ADC_BLOCKS_PER_BUFFER);
    Serial.print("Input samples/sec/channel: ");
    Serial.println((double)(buffers_written * ADC_BLOCKS_PER_BUFFER * GENERATED_SAMPLES_PER_BLOCK) * 1000000. / ((double)(now - start_time)));
    Serial.print("Output samples/sec/channel: ");
    Serial.println((double)(buffers_written * ADC_BLOCKS_PER_BUFFER * GENERATED_SAMPLES_PER_BLOCK / 4) * 1000000. / ((double)(now - start_time)));
    Serial.print("Output bytes/sec: ");
    Serial.println((double)(buffers_written * OUTPUT_BUFFER_SIZE * sizeof (uint16_t)) * 1000000. / ((double)(now - start_time)));
    Serial.print("Max Delta: ");
    Serial.print(delta_max);
    Serial.println(" usec");
    if (reduce_errors) {
      Serial.print("****    reduce errors: ");
      Serial.println(reduce_errors);
    }
#ifdef IL_LOGGING
    il_dump();
#endif
  }
  delta = micros() - now;
  if (delta > delta_max)
    delta_max = delta;
}

/*
   Warning: this loop function is called from within the TC5 ISR.
   Keep it brief!
   As dummy load, this routine blinks the LED and consumes 10.1% of the CPU.
*/
static void myLoop() {
  count_clicks++;
  if (divider++ >= DIVIDE_VAL) {
    divider = 0;
    if (led_val == HIGH)
      led_val = LOW;
    else
      led_val = HIGH;
    digitalWrite(LED_PIN, led_val);
  }
  delayMicroseconds(400); /// 200 == 10% of the CPU
}
