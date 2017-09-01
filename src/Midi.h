#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

class Midi : public ofxMidiListener {
private:
    ofxMidiIn                   midiInput;
    ofxMidiOut                  midiOutput;
    
    ofxMidiMessage              midiMessage;
    
    const int                   width = 8;
    const int                   height = 8;
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
    vector<int>                 agentPos;
    
    // Grid of launchpad midi note values we want
    vector<int>                 midiGrid = {
        0,1,2,3,4,5,6,7,
        16,17,18,19,20,21,22,23,
        32,33,34,35,36,37,38,39,
        48,49,50,51,52,53,54,55,
        64,65,66,67,68,69,70,71,
        80,81,82,83,84,85,86,87,
        96,97,98,99,100,101,102,103,
        112,113,114,115,116,117,118,119
    };
    
    int                         midiIndexOf(int val);
public:
    Midi();
    ~Midi();
    
    bool                        setup(int port);
    bool                        setup(string device);
    
    void                        update();
    
    vector<bool>                getGrid();
    void                        updateAgentPos(int agent, int pos);
    
    void                        newMidiMessage(ofxMidiMessage & eventArgs);
};
