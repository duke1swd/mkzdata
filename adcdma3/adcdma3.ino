/*
   This program tests continuous DMA from the ADC into memory buffers.

   The program is built around the assumption we are scanning 6 analog pins.
   We do some simple digital filtering on the input pins as part of downsampling.
*/

// Each data point is 16 bits.  Each sample is one point from each of 8 channels
// A sample is 16 bytes
struct sample_s {
  uint16_t c0;
  uint16_t c1;
  uint16_t c2;
  uint16_t c3;
  uint16_t null0;
  uint16_t null1;
  uint16_t c4;
  uint16_t c5;
};


// A block is the amount we DMA before we interrupt
// For now it is 16 samples.  Since we are doing a 16-input filter, this is the minimum we can do
// and guarantee that the filter needs inputs from only 2 buffers.
// A block is 16*16 = 256 bytes
// We keep three blocks in memory, so 768B of memory
// Tagged as volatile because these are written by DMA, read by CPU
volatile struct adc_block_s {
  struct sample_s s0;
  struct sample_s s1;
  struct sample_s s2;
  struct sample_s s3;
  struct sample_s s4;
  struct sample_s s5;
  struct sample_s s6;
  struct sample_s s7;
  struct sample_s s8;
  struct sample_s s9;
  struct sample_s s10;
  struct sample_s s11;
  struct sample_s s12;
  struct sample_s s13;
  struct sample_s s14;
  struct sample_s s15;
} adc_b0, adc_b1, adc_b2;

// The filter takes 16 inputs.  It should have 16 coefficients, but we assume
// the filter is symmetric, so the first and last coeeficient are the same, etc.
// The floating point values are scaled by 2^16 to make the integer part of the
// result in the high order 16 bits.  Then scaled by 2^4 because we are taking
// 12-bit numbers as input and want 16-bit numbers as output
#define	C_CONV(v) ((uint32_t)((v) * (double)(1<<20)))
#define	C7	C_CONV(1./3.)
#define	C6	C_CONV(1./9.)
#define	C5	C_CONV(1./27.)
#define	C4	C_CONV(1./81.)
#define	C3	C_CONV(1./243.)
#define	C2	C_CONV(1./729.)
#define	C1	C_CONV(1./2187.)
#define	C0	C_CONV(1./6561.)

#define	OUTPUTS_PER_BLOCK	(4 * 6)	// 16 samples generates 4 outputs on 6 channels
#define	HEADER_SIZE		4	// reserve 4 * 16 = 2 * 32 bits for header
#define	N_OUTPUT_BUFFERS	2
#define	OUTPUT_BUFFER_SIZE	2048	// in samples, not bytes

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

#define ADCPIN0 A3		// A3 _must_ be the base pin.  Others are not consecutive.
#define ADCPIN1 A4
#define ADCPIN2 A5
#define ADCPIN3 A6
#define ADCPIN4 A1
#define ADCPIN5 A2
#define NPINS 8			// XXX QQQQ should be 8 QQQQ XXX
#define	N_DMA_CHANNELS 1		// This is the number of DMA channels we use.  There are 12, but we don't use them all.

// Interrupt logging stuff
#define	IL_MAX	16
uint32_t il_times[IL_MAX];
uint8_t il_reasons[IL_MAX];

#define	IL_START	0x8
#define	IL_TDONE	0x2
#define	IL_TERR		0x1
#define	IL_SUSP		0x4
uint16_t il_overflow;
uint8_t il_count;

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

void init_buffer() {
  uint32_t t;
  buffer_status[current_buffer] = FILLING;
  output_pointer = buffers[current_buffer];
  // Put some header info into the buffer.  Not sure what.
  *output_pointer = 0x1234;
  output_pointer += HEADER_SIZE;
  // how many more samples can we put in this buffer?
  output_counter = (OUTPUT_BUFFER_SIZE - HEADER_SIZE) / OUTPUTS_PER_BLOCK;
}

static uint32_t chnl = 0;  // DMA channel
volatile uint32_t dmadone;
volatile uint32_t cpu_c;

// Apparently this is called on the listed interrupts.
// I'm unaware of how this happens.
// All it appears to do is clear the interrupts and set the dmadone variable.
void DMAC_Handler() {
  int i;
  uint32_t bf_desc;

  // interrupts DMAC_CHINTENCLR_TERR DMAC_CHINTENCLR_TCMPL DMAC_CHINTENCLR_SUSP
  // These are transfer error, transfer complete, and DMA suspended
  uint8_t active_channel;

  // disable irqs ?  Not sure why this is necessary.  Perhaps to prevent recursive calls?
  __disable_irq();
  active_channel =  DMAC->INTPEND.reg & DMAC_INTPEND_ID_Msk; // get channel number
  DMAC->CHID.reg = DMAC_CHID_ID(active_channel);
  dmadone = DMAC->CHINTFLAG.reg;	// huh?

  il_times[il_count] = micros();
  il_reasons[il_count] = (dmadone & 0x7);

  DMAC->CHINTFLAG.reg = DMAC_CHINTENCLR_TCMPL; // clear
  DMAC->CHINTFLAG.reg = DMAC_CHINTENCLR_TERR;
  DMAC->CHINTFLAG.reg = DMAC_CHINTENCLR_SUSP;

  // which descriptor are we using?
  bf_desc = wrb[0].dstaddr;
#include "reduce.h"
else reduce_errors++;

#if 0
  for (i = 0; i < 10; i++) {
    cpu_c += 1;
    cpu_c += 1;
  }
#endif

  if (--output_counter <= 0) {
    buffer_status[current_buffer] = FULL;
    current_buffer++;
    if (current_buffer >= N_OUTPUT_BUFFERS) {
      current_buffer = 0;
    }
    // Put code to deal with overrun here.
    init_buffer();
  }

  if (il_count >= IL_MAX - 1) {
    il_overflow++;
  } else {
    il_count++;
  }
  __enable_irq();

}


// PM stands for Power Manager.  See chapter 16
// Note that APB is the standard ARM peripheral bus, while AHB is the standard ARM high-performance bus.
// THhere is one AHB that is sync'd to the CPU core, and three) APBs (a thru c) that are async, and go through
// an AHB to APB bus bridge.
// Note that the burst length is hardwired to 1 beat.
void dma_init() {
  il_overflow = 0;
  il_count = 1;
  il_reasons[0] = IL_START;
  // probably on by default
  // The DMAC controller requires both an AHB and an APB clock to be up and running.  See 20.5.3
  PM->AHBMASK.reg |= PM_AHBMASK_DMAC ;
  PM->APBBMASK.reg |= PM_APBBMASK_DMAC ;
  NVIC_EnableIRQ( DMAC_IRQn ) ;

  DMAC->BASEADDR.reg = (uint32_t)descriptor_section;
  DMAC->WRBADDR.reg = (uint32_t)wrb;
  DMAC->CTRL.reg = DMAC_CTRL_DMAENABLE | DMAC_CTRL_LVLEN(0xf);	// this enables the DMAC and all 4 of its arbitration levels
}

void adc_dma() {
  uint32_t temp_CHCTRLB_reg;
  int i, j;

  DMAC->CHID.reg = DMAC_CHID_ID(chnl);		// hard wired in this code to channel 0.
  DMAC->CHCTRLA.reg &= ~DMAC_CHCTRLA_ENABLE;	// Disable the channel
  DMAC->CHCTRLA.reg = DMAC_CHCTRLA_SWRST;	// Reset the channel.  Return to defaults
  // not sure why this is necessary, or even harmless.
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
  Serial.print("init output count: ");
  Serial.println(output_counter);

  // start channel
  il_times[0] = micros();
  DMAC->CHID.reg = DMAC_CHID_ID(chnl);
  DMAC->CHCTRLA.reg |= DMAC_CHCTRLA_ENABLE;
}

// Not sure this routine is needed.
static __inline__ void ADCsync() __attribute__((always_inline, unused));
static void   ADCsync() {
  while (ADC->STATUS.bit.SYNCBUSY == 1); //Just wait till the ADC is free
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
  //ADC->REFCTRL.bit.REFSEL = ADC_REFCTRL_REFSEL_INTVCC0_Val; //  2.2297 V Supply VDDANA
  //ADC->INPUTCTRL.bit.GAIN = ADC_INPUTCTRL_GAIN_1X_Val;      // Gain select as 1X
  //ADC->INPUTCTRL.bit.GAIN = ADC_INPUTCTRL_GAIN_DIV2_Val;  // default
  ADC->REFCTRL.bit.REFSEL = ADC_REFCTRL_REFSEL_INTVCC1_Val;
  ADCsync();    //  ref 31.6.16
  // first pin to scan
  itemp = g_APinDescription[ADCPIN0].ulADCChannelNumber << ADC_INPUTCTRL_MUXPOS_Pos;
  // Scan 4 pins
  itemp |= ADC_INPUTCTRL_INPUTSCAN(NPINS);
  // set the gain
  itemp |= ADC_INPUTCTRL_GAIN_1X;
  // set the INPUTRCTRL register
  ADC->INPUTCTRL.reg = itemp;
  ADCsync();
  ADC->AVGCTRL.reg = 0x00 ;       //no averaging
  ADC->SAMPCTRL.reg = 0x00;  ; //sample length in 1/2 CLK_ADC cycles
  ADCsync();
  ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV8 | ADC_CTRLB_FREERUN | ADC_CTRLB_RESSEL_12BIT;
  ADCsync();
  ADC->CTRLA.bit.ENABLE = 0x01;
  ADCsync();
}

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

void setup() {
  Serial.begin(9600);
  while (!Serial) ;
  Serial.println("Hello World");
  measure("idle cpu");

  analogWriteResolution(10);
  analogWrite(A0, 64);  // test with DAC
  adc_init();
  Serial.println("adc_init complete");
  dma_init();
  Serial.println("dma_init complete");
  adc_dma();
  delay(100);
  il_dump();
  measure("during DMA");
  il_dump();
  Serial.print("Reduce Errors: ");
  Serial.println(reduce_errors);
}

void loop() {
}
