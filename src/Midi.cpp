#include "Midi.h"

//--------------------------------------------------------------
// Constructor -------------------------------------------------
Midi::Midi() {
    // Flush any left open ports
    midiOutput.closePort();
    midiInput.closePort();
    agentPos.resize(4);
}

//--------------------------------------------------------------
// Private Functions -------------------------------------------
// Find the index of a midi note number from the midiGrid array
int Midi::midiIndexOf(int val) {
    int index;
    vector<int>::iterator it;
    
    it = find(midiGrid.begin(), midiGrid.end(), val);
    index = distance(midiGrid.begin(), it);
    
    return index;
}


//--------------------------------------------------------------
// Public Functions --------------------------------------------
// Setup can take either the midi port number or its device name
bool Midi::setup(int port) {
    bool connected = midiInput.openPort(port);
    
    if (connected) {
        midiOutput.openPort(port);
        // Ignore sysex, timing, and active sense messages
        midiInput.ignoreTypes(true, true, true);
        midiInput.addListener(this);
        
        // Clear any stale midi messages
        for (int i = 0; i < midiGrid.size(); i++) {
            midiOutput << NoteOff(1, midiGrid[i], 0);
        }
    }
    
    return connected;
}

bool Midi::setup(string device) {
    bool connected = midiInput.openPort(device);
    
    if (connected) {
        midiOutput.openPort(device);
        // Ignore sysex, timing, and active sense messages
        midiInput.ignoreTypes(true, true, true);
        midiInput.addListener(this);
        
        // Clear any stale midi messages
        for (int i = 0; i < midiGrid.size(); i++) {
            midiOutput << NoteOff(1, midiGrid[i], 0);
        }
    }
    
    return connected;
}

void Midi::close() {
    midiOutput.closePort();
    midiInput.closePort();
    midiInput.removeListener(this);
}

//--------------------------------------------------------------
// Keep track of how many blocks are active
void Midi::update() {
    int activeCount = 0;
    for (int i = 0; i < grid.size(); i++) {
        if (grid[i]) {
            activeCount++;
        }
    }
    numActive = activeCount;
}

// Use to template the whole grid from elsewhere in the program
void Midi::updateGridFromTemplate(int i) {
    switch (i) {
        case 0:
            if (previousTemplate != 0) {
                numActive = 0;
                previousTemplate = 0;
                grid = template_0;
                for (int i = 0; i < grid.size(); i++) {
                    grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
                }
            }
            break;
        case 1:
            if (previousTemplate != 1) {
                numActive = 28;
                previousTemplate = 1;
                grid = template_1;
                for (int i = 0; i < grid.size(); i++) {
                    grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
                }
            }
            break;
        case 2:
            if (previousTemplate != 2) {
                numActive = 16;
                previousTemplate = 2;
                grid  = template_2;
                for (int i = 0; i < grid.size(); i++) {
                    grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
                }
            }
            break;
        case 3:
            if (previousTemplate != 3) {
                numActive = 38;
                previousTemplate = 3;
                grid  = template_3;
                for (int i = 0; i < grid.size(); i++) {
                    grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
                }
            }
            break;
        case 4:
            if (previousTemplate != 4) {
                numActive = 40;
                previousTemplate = 4;
                grid  = template_4;
                for (int i = 0; i < grid.size(); i++) {
                    grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
                }
            }
            break;
        case 5:
            if (previousTemplate != 5) {
                numActive = 28;
                previousTemplate = 5;
                grid  = template_5;
                for (int i = 0; i < grid.size(); i++) {
                    grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
                }
            }
            break;
        case 6:
            if (previousTemplate != 6) {
                numActive = 28;
                previousTemplate = 6;
                grid  = template_6;
                for (int i = 0; i < grid.size(); i++) {
                    grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
                }
            }
            break;
        case 7:
            if (previousTemplate != 7) {
                numActive = 40;
                previousTemplate = 7;
                grid  = template_7;
                for (int i = 0; i < grid.size(); i++) {
                    grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
                }
            }
            break;
        default:
            break;
    }
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
    
    switch (midiMessage.pitch) {
        case 8:
            if (previousTemplate != 0) {
                numActive = 0;
                previousTemplate = 0;
                grid = template_0;
                for (int i = 0; i < grid.size(); i++) {
                    grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
                }
            }
            break;
        case 24:
            if (previousTemplate != 1) {
                numActive = 28;
                grid = template_1;
                for (int i = 0; i < grid.size(); i++) {
                    grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
                }
            }
            break;
        case 40:
            if (previousTemplate != 2) {
                numActive = 16;
                grid  = template_2;
                for (int i = 0; i < grid.size(); i++) {
                    grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
                }
            }
            break;
        case 56:
            if (previousTemplate != 3) {
                numActive = 38;
                grid  = template_3;
                for (int i = 0; i < grid.size(); i++) {
                    grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
                }
            }
            break;
        case 72:
            if (previousTemplate != 4) {
                numActive = 40;
                grid  = template_4;
                for (int i = 0; i < grid.size(); i++) {
                    grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
                }
            }
            break;
        case 88:
            if (previousTemplate != 5) {
                numActive = 28;
                grid  = template_5;
                for (int i = 0; i < grid.size(); i++) {
                    grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
                }
            }
            break;
        case 104:
            if (previousTemplate != 6) {
                numActive = 28;
                grid  = template_6;
                for (int i = 0; i < grid.size(); i++) {
                    grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
                }
            }
            break;
        case 120:
            if (previousTemplate != 7) {
                numActive = 40;
                grid  = template_7;
                for (int i = 0; i < grid.size(); i++) {
                    grid[i] ? midiOutput << NoteOn(1, midiGrid[i], 11) : midiOutput << NoteOff(1, midiGrid[i], 0);
                }
            }
            break;
        default:
            if (midiMessage.velocity > 9) {
                int index = midiIndexOf(midiMessage.pitch);
                if (index >= 0 && index < midiGrid.size()) {
                    bool gridReverse = !grid[index];
                    
                    if (gridReverse && numActive < 54) {
                        grid[index] = gridReverse;
                        midiOutput << NoteOn(1, midiGrid[index], 11);
                    } else {
                        grid[index] = gridReverse;
                        midiOutput << NoteOff(1, midiGrid[index], 0);
                    }
                }
            }
            break;
    }
}
