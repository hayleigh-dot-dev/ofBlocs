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
    
    ofLog(OF_LOG_NOTICE, ofToString(midiMessage.pitch));
    
    switch (midiMessage.pitch) {
        case 8:
            grid = template_0;
            for (int i = 0; i < grid.size(); i++) {
                grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
            }
            break;
        case 24:
            grid = template_1;
            for (int i = 0; i < grid.size(); i++) {
                grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
            }
            break;
        case 40:
            grid  = template_2;
            for (int i = 0; i < grid.size(); i++) {
                grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
            }
            break;
        case 56:
            grid  = template_3;
            for (int i = 0; i < grid.size(); i++) {
                grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
            }
            break;
        case 72:
            grid  = template_4;
            for (int i = 0; i < grid.size(); i++) {
                grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
            }
            break;
        case 88:
            grid  = template_5;
            for (int i = 0; i < grid.size(); i++) {
                grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
            }
            break;
        case 104:
            grid  = template_6;
            for (int i = 0; i < grid.size(); i++) {
                grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
            }
            break;
        case 120:
            grid  = template_7;
            for (int i = 0; i < grid.size(); i++) {
                grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
            }
            break;
        default:
            if (midiMessage.velocity > 0) {
                int index = midiIndexOf(midiMessage.pitch);
                if (index >= 0 && index < midiGrid.size()) {
                    grid[index] = !grid[index];
                    grid[index] ? midiOutput << NoteOn(1, midiGrid[index], 11) : midiOutput << NoteOff(1, midiGrid[index], 0);
                }
            }
            break;
    }
}
