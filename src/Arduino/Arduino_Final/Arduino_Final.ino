int grid[8];
const int s0 = 2;
const int s1 = 3;
const int s2 = 4;
// Pointer used to set which grid to output

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
    grid[i] = analogRead(A0) / 4;
  }
  
  if (Serial.available() > 0) {
    byte byteRead = Serial.read();
    switch (byteRead) {
      // oF requests a grid update
      case 255:
        for(int i = 0; i < 8; i++) {
          Serial.write(grid[i]);
        }
        break;
      case 1:

        break;
      default:

        break;
    } 
  }
}


