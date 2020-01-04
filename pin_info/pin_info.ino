volatile uint32_t counter;

void setup() {
  uint32_t t1, t2, i;
  
  Serial.begin(9600);
  while (!Serial) ;
  analogRead(A0);
  Serial.println(g_APinDescription[A0].ulADCChannelNumber);
  analogRead(A1);
  Serial.println(g_APinDescription[A1].ulADCChannelNumber);
  analogRead(A2);
  Serial.println(g_APinDescription[A2].ulADCChannelNumber);
  analogRead(A3);
  Serial.println(g_APinDescription[A3].ulADCChannelNumber);
  analogRead(A4);
  Serial.println(g_APinDescription[A4].ulADCChannelNumber);
  analogRead(A5);
  Serial.println(g_APinDescription[A5].ulADCChannelNumber);
  analogRead(A6);
  Serial.println(g_APinDescription[A6].ulADCChannelNumber);

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
