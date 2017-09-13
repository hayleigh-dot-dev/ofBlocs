int s0 = 2;
int s1 = 3;
int s2 = 4;

void setup() {
  Serial.begin(9600);

  // Mux control pins
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);

    for (int i = 8; i < 14; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
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

    Serial.print("[");
    Serial.print(i);
    Serial.print(":  ");
    Serial.print(val);
    Serial.print("]");
  }
  Serial.println("");
  delay(1000);
}
