#include "Arduino.h"

//--------------------------------------------------------------
// Constructor -------------------------------------------------
Arduino::Arduino() {
    grid.resize(width * height);
}

//--------------------------------------------------------------
// Private Functions -------------------------------------------

//--------------------------------------------------------------
// Public Functions --------------------------------------------
bool Arduino::setup(int port, int baud) {
	bool isConnected = arduino.setup(port, baud);
    
    // Request grid from arduino
    if (arduino.isInitialized()) {
        arduino.writeByte(255);

        unsigned char data[64];
        arduino.readBytes(data, 64);

        for (int i = 0; i < 64; i++) {
            // Explicit char -> bool conversion
            grid[i] = static_cast<bool>(data[i]);
        }
    }
    return isConnected;
}

bool Arduino::setup(string device, int baud) {
    bool isConnected = arduino.setup(device, baud);
    
    // Request grid from arduino
    if (arduino.isInitialized()) {
        arduino.writeByte(255);

        unsigned char data[64];
        arduino.readBytes(data, 64);

        for (int i = 0; i < 64; i++) {
            // Explicit char -> bool conversion
            grid[i] = static_cast<bool>(data[i]);
        }
    }
    return isConnected;
}

//--------------------------------------------------------------
void Arduino::update() {
    // Request grid from arduino
    if (arduino.isInitialized()) {
        arduino.writeByte(255);

        unsigned char data[64];
        arduino.readBytes(data, 64);

        for (int i = 0; i < 64; i++) {
            // Explicit char -> bool conversion
            grid[i] = static_cast<bool>(data[i]);
        }
    }
}

//--------------------------------------------------------------
void Arduino::setPos(int i) {

}

void Arduino::setPos(int x, int y) {
    
}

//--------------------------------------------------------------
vector<bool> Arduino::getGrid() {
    return grid;
}
