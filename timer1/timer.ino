/*
 * This program implements a control loop running off a 1KHz timer interrupt.
 *
 * The timer control code is modeled on the Tone library.  It uses the
 * same timer as the Tone library, but I see no need to support tone
 * generation in this project.
 */

#define CTRL_TC         TC5
#define CTRL_TC_IRQn    TC5_IRQn
#define CTRL_TC_TOP     0xFFFF
#define CTRL_TC_CHANNEL 0

void TC5_Handler (void) __attribute__ ((weak, alias("Control Loop")));

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

void start_control_loop()
{
  // Configure interrupt request
  NVIC_DisableIRQ(CTRL_TC_IRQn);
  NVIC_ClearPendingIRQ(CTRL_TC_IRQn);
  
  NVIC_SetPriority(TONE_TC_IRQn, 0);
      
  // Enable GCLK for TC4 and TC5 (timer counter input clock)
  GCLK->CLKCTRL.reg = (uint16_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID(GCM_TC4_TC5));
  while (GCLK->STATUS.bit.SYNCBUSY);

  resetTC(CTRL_TC);

  uint16_t tmpReg = 0;
  tmpReg |= TC_CTRLA_MODE_COUNT16;  // Set Timer counter Mode to 16 bits
  tmpReg |= TC_CTRLA_WAVEGEN_MFRQ;  // Set TONE_TC mode as match frequency
  tmpReg |= TC_CTRLA_PRESCALER_DIV2;// Set Prescaler to 2x
  TONE_TC->COUNT16.CTRLA.reg |= tmpReg;
  WAIT_TC16_REGS_SYNC(TONE_TC)

  TONE_TC->COUNT16.CC[TONE_TC_CHANNEL].reg = (uint16_t) ccValue;
  WAIT_TC16_REGS_SYNC(TONE_TC)

  portToggleRegister = &(PORT->Group[g_APinDescription[outputPin].ulPort].OUTTGL.reg);
  portClearRegister = &(PORT->Group[g_APinDescription[outputPin].ulPort].OUTCLR.reg);
  portBitMask = (1ul << g_APinDescription[outputPin].ulPin);

  // Enable the TONE_TC interrupt request
  TONE_TC->COUNT16.INTENSET.bit.MC0 = 1;
  
  if (outputPin != lastOutputPin)
  {
    lastOutputPin = outputPin;
    digitalWrite(outputPin, LOW);
    pinMode(outputPin, OUTPUT);
    toneIsActive = true;
  }

  // Enable TONE_TC
  TONE_TC->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;
  WAIT_TC16_REGS_SYNC(TONE_TC)
  
  NVIC_EnableIRQ(TONE_TC_IRQn);
}


// CPU measurement code
volatile uint32_t cpu_c;
void measure(char *name) {
  uint32_t t1, t2, i;

  t1 = micros();
  for (i = 0; i < 1000000; i++) {
    cpu_c += 1;
    cpu_c += 1;
  }
  t2 = micros();
  Serial.println(name);
  Serial.print("  ");
  Serial.println(t2 - t1);
}


void setup() {
  Serial.begin(9600);
  while (!Serial) ;
  measure("idle cpu");
  analogWriteResolution(10);
  delay(100);
  measure("control loop running");
}

void loop() {
}
