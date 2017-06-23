#pragma once

#include "ofMain.h"
#include "ofSerial.h"

#include "Agent.h"
#include "Agent_System.h"

#include "PureData.h"

class ofApp : public ofBaseApp{
private:
	Agent_System            agentSystem;
	ofSerial				serial;
    PureData                pd;

	int						timer = 0;

public:
	void					setup();
	void					update();
	void					draw();
    
    void                    audioReceived(float * input, int bufferSize, int nChannels);
    void                    audioRequested(float * output, int bufferSize, int nChannels);
};
