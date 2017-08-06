#pragma once

#include "ofMain.h"
#include "ofxPd.h"

class PureData {
private:
    ofxPd                       pd;
public:
    PureData();
    
    bool                        setup(const int numOutChannels,
                                      const int numInChannels,
                                      const int sampleRate,
                                      const int ticksPerBuffer=32,
                                      bool queued=false);
    
    void                        audioIn(float * input, int bufferSize, int nChannels);
    void                        audioOut(float * output, int bufferSize, int nChannels);
    
    void                        openPatch(string path);
    
    void                        sendBang(string r);
};
