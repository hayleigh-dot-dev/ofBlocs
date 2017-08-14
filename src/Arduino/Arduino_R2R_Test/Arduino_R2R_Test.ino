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
}

void loop() {
  for (int i = 0; i < 256; i++) {
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
    
    int val = analogRead(A0);
    
    Serial.print(i, BIN);
    Serial.println(" {");
      Serial.print("  ");
      Serial.println(val);
    Serial.println("}");
  
    delay(500);
  }
}
