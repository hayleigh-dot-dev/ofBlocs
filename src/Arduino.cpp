#include "Arduino.h"

//--------------------------------------------------------------
// Constructor -------------------------------------------------
Arduino::Arduino() {
    //grid.resize(width * height);
}

//--------------------------------------------------------------
// Private Functions -------------------------------------------

//--------------------------------------------------------------
// Public Functions --------------------------------------------
bool Arduino::setup(int port, int baud) {
    arduino.close();
	bool isConnected = arduino.setup(port, baud);
    
    // Request grid from arduino
    if (arduino.isInitialized()) {
        arduino.writeByte(255);

        unsigned char data[8];
        arduino.readBytes(data, 8);

        for (int i = 0; i < 8; i++) {
            // Explicit char -> bool conversion
            grid[i] = static_cast<int>(data[i]);
        }
    }
    return isConnected;
}

bool Arduino::setup(string device, int baud) {
    arduino.close();
    bool isConnected = arduino.setup(device, baud);
    
    // Request grid from arduino
    if (arduino.isInitialized()) {
        arduino.writeByte(255);

        unsigned char data[8];
        arduino.readBytes(data, 8);

        for (int i = 0; i < 8; i++) {
            grid[i] = static_cast<int>(data[i]);
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
        arduino.readBytes(data, 8);

        for (int i = 0; i < 8; i++) {
            grid[i] = static_cast<int>(data[i]);
//            ofLog(OF_LOG_NOTICE, ofToString(i) + ": " + ofToString(grid[i]));
        }
    }
}

//--------------------------------------------------------------
void Arduino::setPos(int i) {

}

void Arduino::setPos(int x, int y) {
    
}

//--------------------------------------------------------------
vector<int> Arduino::getGrid() {
    return grid;
}
