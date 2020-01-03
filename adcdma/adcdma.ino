// adcdma
//  analog A1
//   could use DAC to provide input voltage   A0
//   http://www.atmel.com/Images/Atmel-42258-ASF-Manual-SAM-D21_AP-Note_AT07627.pdf pg 73

// Annotated by SWD, 1/1/20.

#define ADCPIN A1
#define HWORDS 1024
uint16_t adcbuf[HWORDS];

// This structure is more-or-less defined on page 307, figure 20-3.
// The details are in section 20.10
typedef struct {
  uint16_t btctrl;
  uint16_t btcnt;
  uint32_t srcaddr;
  uint32_t dstaddr;
  uint32_t descaddr;
} dmacdescriptor ;
volatile dmacdescriptor wrb[12] __attribute__ ((aligned (16)));		// this is a region in memory where the descriptors will be written back.
dmacdescriptor descriptor_section[12] __attribute__ ((aligned (16)));	// the source descriptors
dmacdescriptor descriptor __attribute__ ((aligned (16)));		// a descriptor?


static uint32_t chnl = 0;  // DMA channel
volatile uint32_t dmadone;

// Apparently this is called on the listed interrupts.
// I'm unaware of how this happens.
// All it appears to do is clear the interrupts and set the dmadone variable.
void DMAC_Handler() {
  // interrupts DMAC_CHINTENCLR_TERR DMAC_CHINTENCLR_TCMPL DMAC_CHINTENCLR_SUSP
// I believe this are transfer error, transfer complete, and some sort of suspend thing
  uint8_t active_channel;

  // disable irqs ?
  __disable_irq();
  active_channel =  DMAC->INTPEND.reg & DMAC_INTPEND_ID_Msk; // get channel number
  DMAC->CHID.reg = DMAC_CHID_ID(active_channel);
  dmadone = DMAC->CHINTFLAG.reg;
  DMAC->CHINTFLAG.reg = DMAC_CHINTENCLR_TCMPL; // clear
  DMAC->CHINTFLAG.reg = DMAC_CHINTENCLR_TERR;
  DMAC->CHINTFLAG.reg = DMAC_CHINTENCLR_SUSP;
  __enable_irq();
}


// PM stands for Power Manager.  See chapter 16
// Note that APB is the standard ARM peripheral bus, while AHB is the standard ARM high-performance bus.
// THhere is one AHB that is sync'd to the CPU core, and three) APBs (a thru c) that are async, and go through
// an AHB to APB bus bridge.
// Note that the burst length is hardwired to 1 beat.
void dma_init() {
  // probably on by default
// The DMAC controller requires both an AHB and an APB clock to be up and running.  See 20.5.3
  PM->AHBMASK.reg |= PM_AHBMASK_DMAC ;
  PM->APBBMASK.reg |= PM_APBBMASK_DMAC ;
  NVIC_EnableIRQ( DMAC_IRQn ) ;

  DMAC->BASEADDR.reg = (uint32_t)descriptor_section;
  DMAC->WRBADDR.reg = (uint32_t)wrb;
  DMAC->CTRL.reg = DMAC_CTRL_DMAENABLE | DMAC_CTRL_LVLEN(0xf);	// this enables the DMAC and all 4 of its arbitration levels
}

void adc_dma(void *rxdata,  size_t hwords) {
  uint32_t temp_CHCTRLB_reg;

  DMAC->CHID.reg = DMAC_CHID_ID(chnl);		// hard wired in this code to channel 0.
  DMAC->CHCTRLA.reg &= ~DMAC_CHCTRLA_ENABLE;	// Disable the channel
  DMAC->CHCTRLA.reg = DMAC_CHCTRLA_SWRST;	// Reset the channel.  Return to defaults
  DMAC->SWTRIGCTRL.reg &= (uint32_t)(~(1 << chnl)); // according to 20.8, writing a 1 will trigger the channel
// set the CHCTRLB register to:
//	level 0 (highest?)
//	source is ADC_DMAC_ID_RESRDY: an ADC result is ready
//	action is BEAT, do one beat.
//	Most of these are not defined in the data sheet.
  temp_CHCTRLB_reg = DMAC_CHCTRLB_LVL(0) |
                     DMAC_CHCTRLB_TRIGSRC(ADC_DMAC_ID_RESRDY) | DMAC_CHCTRLB_TRIGACT_BEAT;
  DMAC->CHCTRLB.reg = temp_CHCTRLB_reg;
  DMAC->CHINTENSET.reg = DMAC_CHINTENSET_MASK ; // enable all 3 interrupts
  dmadone = 0;
  descriptor.descaddr = 0;
  descriptor.srcaddr = (uint32_t) &ADC->RESULT.reg;
  descriptor.btcnt =  hwords;
// why is the dstaddr set to beyond the end of the buffer?
  descriptor.dstaddr = (uint32_t)rxdata + hwords * 2; // end address
// the beat size is a half-word (16 bits), we increment the destination, and the descriptor is valid.
// Note that we do not set a setp size, nor a source increment
// Note that we do not set a block action.  So no interrupt on end of block, only end of transfer, I guess.
  descriptor.btctrl =  DMAC_BTCTRL_BEATSIZE_HWORD | DMAC_BTCTRL_DSTINC | DMAC_BTCTRL_VALID;
// Put the descriptor where it goes.  Not sure how we know the other descriptors are not valid.  Mem is zeroed?
  memcpy(&descriptor_section[chnl], &descriptor, sizeof(dmacdescriptor));

  // start channel
  DMAC->CHID.reg = DMAC_CHID_ID(chnl);
  DMAC->CHCTRLA.reg |= DMAC_CHCTRLA_ENABLE;
}

static __inline__ void ADCsync() __attribute__((always_inline, unused));
static void   ADCsync() {
  while (ADC->STATUS.bit.SYNCBUSY == 1); //Just wait till the ADC is free
}


void adc_init() {
  analogRead(ADCPIN);  // do some pin init  pinPeripheral()
  ADC->CTRLA.bit.ENABLE = 0x00;             // Disable ADC
  ADCsync();
  //ADC->REFCTRL.bit.REFSEL = ADC_REFCTRL_REFSEL_INTVCC0_Val; //  2.2297 V Supply VDDANA
  //ADC->INPUTCTRL.bit.GAIN = ADC_INPUTCTRL_GAIN_1X_Val;      // Gain select as 1X
  ADC->INPUTCTRL.bit.GAIN = ADC_INPUTCTRL_GAIN_DIV2_Val;  // default
  ADC->REFCTRL.bit.REFSEL = ADC_REFCTRL_REFSEL_INTVCC1_Val;
  ADCsync();    //  ref 31.6.16
  ADC->INPUTCTRL.bit.MUXPOS = g_APinDescription[ADCPIN].ulADCChannelNumber;
  ADCsync();
  ADC->AVGCTRL.reg = 0x00 ;       //no averaging
  ADC->SAMPCTRL.reg = 0x00;  ; //sample length in 1/2 CLK_ADC cycles
  ADCsync();
  ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV16 | ADC_CTRLB_FREERUN | ADC_CTRLB_RESSEL_10BIT;
  ADCsync();
  ADC->CTRLA.bit.ENABLE = 0x01;
  ADCsync();
}


void setup() {
  Serial.begin(9600);
  analogWriteResolution(10);
  analogWrite(A0, 64);  // test with DAC
  adc_init();
  dma_init();
}

void loop() {
  uint32_t t;

  t = micros();
  adc_dma(adcbuf, HWORDS);
  while (!dmadone); // await DMA done isr
  t = micros() - t;
  Serial.print(t);  Serial.print(" us   ");
  Serial.println(adcbuf[0]);
  delay(2000);
}
