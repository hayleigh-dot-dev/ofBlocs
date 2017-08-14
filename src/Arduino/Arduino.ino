int grid[64];

int inA = 2;
int inB = 3;
int inC = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(inA, OUTPUT);
  pinMode(inB, OUTPUT);
  pinMode(inC, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0 && Serial.read() == 256) {
    // start byte
    Serial.write(2);

    int * row;
    
    for (int i = 0; i < 8; i++) {
      setMuxRow(i, inA, inB, inC);

      row = readRow(A0);

      for (int j = 0; j < 8; j++) { 
        Serial.write(row[j]);
      }
    }

    // end byte
    Serial.write(3);
  }
}

void setMuxRow(int row, int a, int b, int c) {
  digitalWrite(a, bitRead(row, 0));
  digitalWrite(b, bitRead(row, 1));
  digitalWrite(b, bitRead(row, 1));
}

int * readRow(int pin) {
  int * r;
  int val = analogRead(A0);

  if (val < 128) {
    r = {0, 0, 0, 0, 0, 0, 0, 0};
  } else if (val < 128 * 2) {
    r = {0, 0, 0, 0, 0, 0, 0, 1};
  } else if (val < 128 * 3) {
    r = {0, 0, 0, 0, 0, 0, 1, 1};
  } else if (val < 128 * 4) {
    r = {0, 0, 0, 0, 0, 1, 1, 1};
  } else if (val < 128 * 5) {
    r = {0, 0, 0, 0, 1, 1, 1, 1};
  } else if (val < 128 * 6) {
    r = {0, 0, 0, 1, 1, 1, 1, 1};
  } else if (val < 128 * 7) {
    r = {0, 0, 1, 1, 1, 1, 1, 1};
  } else if (val < 128 * 8) {
    r = {0, 1, 1, 1, 1, 1, 1, 1};
  } else {
    r = {1, 1, 1, 1, 1, 1, 1, 1};
  }

  return r;
}

