#pragma once

#include "ofMain.h"
#include "ofSerial.h"

class Arduino {
private:
	ofSerial					s;

	vector<bool>                g;
public:
	Arduino();

	void						setup(int port);
	void						update();
};
