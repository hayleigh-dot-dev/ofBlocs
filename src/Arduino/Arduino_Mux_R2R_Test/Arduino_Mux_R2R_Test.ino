int s0 = 10;
int s1 = 11;
int s2 = 12;

byte grid[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  
  // Use pins 2-9 as output
  // PORTD is preferable as it can be set the following ways:
  //  PORTD = B00000001;
  //  PORTD = 1;
  // However, using PORTD disables serial...
  for (int i = 2; i < 10; i++) {
    pinMode(i, OUTPUT);
  }

  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
}

void loop() {
  for (int i = 0, muxPin = 0, gridIndex = 0; i < 256; i++) {
    // Loop through each pin, LSB to MSB
    for (int j = 0; j < 8; j++) {
      int pin = j+2;
      
      // Read the jth bit from i
      // Old style way:
      //   i & 0x01
      //   (i>>1) & 0x01
      //   etc...
      digitalWrite(
        pin, 
        bitRead(i, j)
      );
    }

    // Set which pin to input from mux
    digitalWrite(s0, bitRead(muxPin, 0));
    digitalWrite(s1, bitRead(muxPin, 1));
    digitalWrite(s1, bitRead(muxPin, 1));

    int reading = nearestMultiple(analogRead(A0), 4) >> 2;

    grid[gridIndex] = reading;

    muxPin = (muxPin + 1) % 4;
    gridIndex = (gridIndex + 1) % 8;

    delay(250);

    Serial.println("Grid {");
      for (int j = 0; j < 8; j++) {
        Serial.print("  ");
        Serial.println(grid[j], BIN);
      }
    Serial.println("}");
  }
}

// Clean the input so we only get multiples of 4
int nearestMultiple(int num, int factor) {
    return (num - (num % factor));
}
