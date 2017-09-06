#include "Midi.h"

//--------------------------------------------------------------
// Constructor -------------------------------------------------
Midi::Midi() {
    agentPos.resize(4);
}

//--------------------------------------------------------------
// Private Functions -------------------------------------------
int Midi::midiIndexOf(int val) {
    int index;
    vector<int>::iterator it;
    
    it = find(midiGrid.begin(), midiGrid.end(), val);
    index = distance(midiGrid.begin(), it);
    
    return index;
}


//--------------------------------------------------------------
// Public Functions --------------------------------------------
bool Midi::setup(int port) {
    bool connected = midiInput.openPort(port);
    midiOutput.openPort(port);
    // Ignore sysex, timing, and active sense messages
    midiInput.ignoreTypes(true, true, true);
    midiInput.addListener(this);
    
    // Clear any stale midi messages
    for (int i = 0; i < midiGrid.size(); i++) {
        midiOutput << NoteOff(1, midiGrid[i], 0);
    }
    
    return connected;
}

bool Midi::setup(string device) {
    bool connected = midiInput.openPort(device);
    midiOutput.openPort(device);
    // Ignore sysex, timing, and active sense messages
    midiInput.ignoreTypes(true, true, true);
    midiInput.addListener(this);
    
    // Clear any stale midi messages
    for (int i = 0; i < midiGrid.size(); i++) {
        midiOutput << NoteOff(1, midiGrid[i], 0);
    }
    
    return connected;
}

void Midi::close() {
    midiOutput.closePort();
    midiInput.closePort();
    midiInput.removeListener(this);
}

//--------------------------------------------------------------
void Midi::update() {

}

//--------------------------------------------------------------
void Midi::updateAgentPos(int agent, int pos) {
    // Turn off previous position
    grid[agentPos[agent]] ?
        midiOutput << NoteOn(1, midiGrid[agentPos[agent]], 11) :
        midiOutput << NoteOff(1, midiGrid[agentPos[agent]], 0);
    
    agentPos[agent] = pos;
    midiOutput << NoteOn(1, midiGrid[agentPos[agent]], 127);
    
}

//--------------------------------------------------------------
vector<bool> Midi::getGrid() {
    return grid;
}

//--------------------------------------------------------------
void Midi::newMidiMessage(ofxMidiMessage & msg) {
    midiMessage = msg;
    
    if (midiMessage.velocity > 0) {
        int index = midiIndexOf(midiMessage.pitch);
        if (index >= 0 && index < midiGrid.size()) {
            grid[index] = !grid[index];
            grid[index] ? midiOutput << NoteOn(1, midiGrid[index], 11) : midiOutput << NoteOff(1, midiGrid[index], 0);
        }
    }
}
