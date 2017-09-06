int grid_1[64] = {
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
};

int grid_2[64] = {
  1, 0, 0, 0, 1, 0, 0, 1,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 1, 0, 1,
  0, 0, 1, 1, 0, 0, 0, 1,
  0, 0, 0, 0, 0, 1, 0, 0,
  0, 0, 1, 1, 0, 1, 0, 0,
  1, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 1, 0, 0, 1,
};

// Pointer used to set which grid to output
int * grid;

void setup() {
  Serial.begin(9600);
}

void loop() {

  
  if (Serial.available() > 0) {
    byte byteRead = Serial.read();
    switch (byteRead) {
      // oF requests a grid update
      case 255:
        for(int i = 0; i < 64; i++) {
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


