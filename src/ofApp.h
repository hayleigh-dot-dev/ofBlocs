#pragma once

#include "ofMain.h"
#include "ofSerial.h"

#include "Agent.h"
#include "Agent_System.h"

class ofApp : public ofBaseApp{
private:
	Agent_System			agentSystem;
	ofSerial				serial;

	int						timer = 0;

public:
	void					setup();
	void					update();
	void					draw();	
};
