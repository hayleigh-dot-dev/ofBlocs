#include "Arduino.h"

Arduino::Arduino() {

}

void Arduino::setup(int port) {
	s.setup(port, 9600);
}

void Arduino::update() {

}
