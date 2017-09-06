int s0 = 4;
int s1 = 3;
int s2 = 2;

void setup() {
  Serial.begin(9600);

  // Mux control pins
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
}

void loop() {

  for (int i = 0; i < 8; i++) {
    // Read individual bits from i:
    //  000
    //  001
    //  010
    //  etc...
    digitalWrite(s0, bitRead(i, 0));
    digitalWrite(s1, bitRead(i, 1));
    digitalWrite(s2, bitRead(i, 2));

    // Read y(i) from mux
    int val = analogRead(A0);

    Serial.print("Pin ");
    Serial.print(i);
    Serial.println("{");
      Serial.print("  ");
      Serial.println(val >> 2, BIN);
    Serial.println("}");

    delay(500);
  }
}
