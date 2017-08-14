#pragma once

#include "ofMain.h"
#include "ofSerial.h"

#include "Agent.h"
#include "Agent_System.h"

#include "PureData.h"

#include "Arduino.h"

class ofApp : public ofBaseApp{
private:
	Agent_System                agentSystem;
	ofSerial                    serial;
    PureData                    pd;
    Arduino                     arduino;
    
    vector<bool>                grid = {
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0
    };

	int                         timer = 0;

public:
	void                        setup();
	void                        update();
	void                        draw();
    
    void                        audioReceived(float * input, int bufferSize, int nChannels);
    void                        audioRequested(float * output, int bufferSize, int nChannels);
};
