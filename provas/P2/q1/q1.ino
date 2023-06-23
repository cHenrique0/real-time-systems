int motorPin = 3;

void setup() {
  pinMode(motorPin, OUTPUT);
}

void loop() {
  analogWrite(motorPin, 255);
  delay_s(2);
  analogWrite(motorPin, 128);
  delay_ms(2000);
  analogWrite(motorPin, 0);
  delay_s(1);
}

void delay_ms(unsigned long ms) {
  volatile unsigned long start = millis();
  while (millis() - start < ms);
}

void delay_s(unsigned int s) {
  volatile unsigned long ms = s * 1000;
  delay_ms(ms);
}