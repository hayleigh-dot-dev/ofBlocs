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
  1, 0, 0, 0, 0, 0, 0, 1,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  1, 0, 0, 0, 0, 0, 0, 1,
};

int * grid;

void setup() {
  // Put your setup code here, to run once:
  Serial.begin(9600);

  grid = grid_1;
}

void loop() {
  if (millis() % 10000 > 5000) {
    grid = grid_2;
  } else {
    grid = grid_1;
  }
  
  // Put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    byte byteRead = Serial.read();
    switch (byteRead) {
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


