#include "PureData.h"

//--------------------------------------------------------------
// Constructor -------------------------------------------------
PureData::PureData() {

}

//--------------------------------------------------------------
// Private Functions -------------------------------------------

//--------------------------------------------------------------
// Public Functions --------------------------------------------
bool PureData::setup(const int numOutChannels, const int numInChannels,
                     const int sampleRate, const int ticksPerBuffer,
                     bool queued) {
    if(!pd.init(numOutChannels,
                numInChannels,
                sampleRate,
                ticksPerBuffer,
                queued))
    {
        return false;
    } else {
        return true;
    }
}

void PureData::audioIn(float * input, int bufferSize, int nChannels) {
    pd.audioIn(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void PureData::audioOut(float * output, int bufferSize, int nChannels) {
    pd.audioOut(output, bufferSize, nChannels);
}

//--------------------------------------------------------------
void PureData::openPatch(string path) {
    pd.openPatch(path);
    pd.start();
}

//--------------------------------------------------------------
// r is the receiver in the pd patch
void PureData::sendBang(string r) {
    pd.sendBang(r);
}
