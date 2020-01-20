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
#define	CTRL_CC_VAL	24000	// ticks at 12 MHz, so 500 Hz

void TC5_Handler (void) __attribute__ ((weak, alias("Control_Loop")));

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
  
  NVIC_SetPriority(CTRL_TC_IRQn, 0);
      
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

void Control_Loop (void)
{

    // Clear the interrupt
    CTRL_TC->COUNT16.INTFLAG.bit.MC0 = 1;
    myLoop();
}

#ifdef __cplusplus
}
#endif


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

#define DIVIDE_VAL	100
#define LED_PIN LED_BUILTIN
int divider;
int led_val;
volatile uint32_t count_clicks;

void setup() {
  uint32_t start_t;
  uint32_t clicks;

  Serial.begin(9600);
  while (!Serial) ;
  measure("idle cpu");

  divider = 0;
  count_clicks = 0;
  pinMode(LED_PIN, OUTPUT);
  start_control_loop();

  delay(100);
  measure("control loop running");

  start_t = micros();
  clicks = count_clicks;
  while (micros() - start_t < 10ul * 1000000ul) ;
  clicks = count_clicks - clicks;

  Serial.print("Interrupts Per Second: ");
  Serial.println((double)clicks / 10.);
}

void loop() {
}


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
}
