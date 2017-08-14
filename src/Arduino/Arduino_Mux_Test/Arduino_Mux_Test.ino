int s0 = 8;
int s1 = 9;
int s2 = 10;

void setup() {
  Serial.begin(9600);

  // Mux control pins
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  
  for (int i = 2; i < 6; i++) {
    // Pins are connected to each even terminal on the 4051:
    //  y0, y2, y4, y6 
    pinMode(i, OUTPUT);
  }

  pinMode(13, INPUT);
}

void loop() {
  // Write high to each even 4051 pin
  for (int i = 2; i < 6; i++) {
    digitalWrite(i, HIGH);
  }

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
    int val = digitalRead(13);

    Serial.print("Pin ");
    Serial.print(i);
    Serial.println("{");
      Serial.print("  ");
      Serial.println(val);
    Serial.println("}");

    delay(500);
  }
}
