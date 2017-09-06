void setup() {
  // put your setup code here, to run once:
  for (int i = 8; i < 14; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 8; i < 14; i++) {
    int prevPin = (i - 1) >= 8 ? i - 1 : 8;
    Serial.println(prevPin);
    digitalWrite(prevPin, LOW);
    digitalWrite(i, HIGH);
  }

  for (int i = 13; i >= 8; i--) {
    int prevPin = (i + 1) <= 13 ? i + 1 : 13;
    Serial.println(prevPin);
    digitalWrite(prevPin, LOW);
    digitalWrite(i, HIGH);
    delay(250);
  }
}
