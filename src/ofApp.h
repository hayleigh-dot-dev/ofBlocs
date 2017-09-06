#pragma once

#include "ofMain.h"
#include "ofSerial.h"

#include "Agent.h"
#include "Agent_System.h"
#include "Agent_Utilities.h"

#include "PureData.h"

#include "Arduino.h"
#include "Midi.h"

class ofApp : public ofBaseApp{
private:
    bool                        DEBUG = true;
    int                         framerate = 30;
    
	Agent_System                agentSystem;
    
    PureData                    pd;
    
    ofSerial                    serial;
    
    Arduino                     arduino;
    bool                        isArduinoConnected;
    
    Midi                        launchpad;
    bool                        isMidiConnected;
    
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

    void                        drawDebug();
    void                        updateArduino();
    void                        updateMidi();
public:
	void                        setup();
	void                        update();
	void                        draw();
    void                        exit();
    
    void                        audioReceived(float * input, int bufferSize, int nChannels);
    void                        audioRequested(float * output, int bufferSize, int nChannels);
};
