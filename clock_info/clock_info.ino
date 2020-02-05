//#define C_0 ((uint16_t)0xff00)
#define C_0 65280

volatile uint32_t counter;

void setup() {
  uint32_t t1, t2, i;
  uint16_t s1, s2;

  Serial.begin(9600);
  while (!Serial) ;

  Serial.print("APBCSEL ");
  Serial.println(PM->APBCSEL.reg, HEX);

  // Delay loop testing

  t1 = micros();
  for (i = 0; i < 1000000; i++) {
    counter += 1;
    counter += 1;
  }
  t2 = micros();
  Serial.println(t2 - t1);

  // Some basic math testing
  s1 = 1000;
  s2 = (s1 * C_0) >> 16;

  Serial.print("Math test.  1000 * .996 = ");
  Serial.println(s2);
}

void loop() {
  // put your main code here, to run repeatedly:

}
