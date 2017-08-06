#include "Arduino.h"

//--------------------------------------------------------------
// Constructor -------------------------------------------------
Arduino::Arduino() {

}

//--------------------------------------------------------------
// Private Functions -------------------------------------------

//--------------------------------------------------------------
// Public Functions --------------------------------------------
bool Arduino::setup(int port) {
	arduino.setup(port, 9600);
    
    int time = ofGetElapsedTimeMillis();
    int wait = 500;
    
    size = 0;
    
    while (time + wait < ofGetElapsedTimeMillis()) {
        if (arduino.available()) {
            char readByte = arduino.readByte();
            
            if (readByte == OF_SERIAL_NO_DATA) {
                ofLog(OF_LOG_WARNING, "Arduino::setup: No data read.");
            }
            else if (readByte == OF_SERIAL_ERROR) {
                ofLog(OF_LOG_WARNING, "Arduino::setup: Error reading serial data.");
            }
            else {
                size = readByte;
            }
        }
    }
    
    if (size > 0) {
        return true;
    }
    else {
        ofLog(OF_LOG_ERROR, "Arduino::setup: Size equals 0, error setting up.");
    }
}

//--------------------------------------------------------------
void Arduino::update() {
    
}

//--------------------------------------------------------------
void Arduino::setPos(int i) {
    unsigned char pos = (char) i % size;
    unsigned char data[2] = {pos, 255};
    
    arduino.writeBytes(&data[0], 2);
}

void Arduino::setPos(int x, int y) {
    
}
