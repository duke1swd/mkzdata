volatile uint32_t counter;

void setup() {
  uint32_t t1, t2, i;
  
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
}

void loop() {
  // put your main code here, to run repeatedly:

}
