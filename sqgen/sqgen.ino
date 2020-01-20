#define IOPIN 3
#define LED 13
unsigned long lastTime;
int counter;
int ledState;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello World.  0.5Hz");
  pinMode(IOPIN, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(IOPIN, HIGH);
  lastTime = millis();
  counter = 0;
}

void loop() {
  unsigned long t;

  t = millis();
  if (t != lastTime) {
    lastTime = t;
    if (t & 1) {
      digitalWrite(IOPIN, HIGH);
    } else {
      digitalWrite(IOPIN, LOW);
    }
    counter++;
    if (counter >= 100) {
      counter = 0;
      if (ledState == HIGH)
        ledState = LOW;
      else
        ledState = HIGH;
      digitalWrite(LED, ledState);
    }
  }
}
