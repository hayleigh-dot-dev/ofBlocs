#include "ofApp.h"

#define FRAMERATE 8

//--------------------------------------------------------------
void ofApp::setup(){
    // Framerate effectively sets how often we poll arduino for updates
	ofSetFrameRate(FRAMERATE);

    ofSetBackgroundColor(ofColor::fromHex(0xF7D4BC));

	//----------------------------------------------------------
    // Connect to Arduinos
    serial.listDevices();
    isConnected = arduino.setup(1, 9600);

    if (isConnected) grid = arduino.getGrid();

    //--------------------------------------------------------------
    // Add Agents
    agentSystem.addAgent(8, 8);
    agentSystem.addAgent(8, 8);
    agentSystem.addAgent(8, 8);
    agentSystem.addAgent(8, 8);

    // Update grid for each agent
    for(int i = 0; i < agentSystem.size(); i++) {
        for (int j = 0; j < 64; j++) {
            agentSystem.updateAgentGrid(i, j, grid[j]);
        }
    }
    //--------------------------------------------------------------
    // Borrowed from ofxPd example {
    //   Setup PureData
    
    //   The number of libpd ticks per buffer,
    //   used to compute the audio buffer len: tpb * blocksize (always 64)
    
    //   These are evaluated at compile time
    #ifdef TARGET_LINUX_ARM
        // longer latency for Raspberry PI
        int ticksPerBuffer = 32; // 32 * 64 = buffer len of 2048
        int numInputs = 0; // no built in mic
    #else
        int ticksPerBuffer = 8; // 8 * 64 = buffer len of 512
        int numInputs = 1;
    #endif
    //   setup OF sound stream
    ofSoundStreamSetup(2, numInputs, this, 44100, ofxPd::blockSize()*ticksPerBuffer, 3);
    if(!pd.setup(2, numInputs, 44100, ticksPerBuffer, false)) {
        OF_EXIT_APP(1);
    }
    // }
    
    pd.openPatch("main.pd");
    
    ofSleepMillis(1000);
}

//--------------------------------------------------------------
void ofApp::update(){
    // Arduino update is seperate from recieving the grid
    // This way we can constantly poll arduino for updates without
    // needlessly copying the grid
    arduino.update();
    
    if (timer == 0) {
        grid = arduino.getGrid();
    
        ofLog(OF_LOG_NOTICE, "["+ofToString(ofGetFrameNum())+"]" + "Updating agents:");
        
        for (int i = 0; i < agentSystem.size(); i++) {
            // Demonstrate reference based access to agents
            Agent & selectedAgent = agentSystem.getAgent(i);
        
            for (int i = 0; i < 64; i++) {
                selectedAgent.updateGrid(i, grid[i]);
            }
            
            selectedAgent.update();
        
            int  x = selectedAgent.getX();
            int  y = selectedAgent.getY();
            bool b = selectedAgent.hasCollided();
            
            if (b) {
                ofLog(OF_LOG_NOTICE, "  Agent"+ofToString(i)+ " collision detected");
                // Send a pd bang to the receive object called 'trigger'
                pd.sendBang("trigger");
            }
            ofLog(OF_LOG_NOTICE, "  Agent"+ofToString(i)+" position is: " + ofToString(x) + " : " + ofToString(y));
        }
    }

    // Update agents 2 times per second (effectively 120 bpm)
	timer = ++timer % (FRAMERATE / 4);
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Debugging draw to visual represent grid and agent position
    for (int i = 0; i < 64; i++) {
        int x = (i % 8) * (ofGetWidth() / 8);
        int y = (i / 8) * (ofGetHeight() / 8);
        
        ofPushStyle();
            if (grid[i]) {
                ofSetHexColor(0x1F2332);  
                ofDrawRectangle(x, y, ofGetWidth() / 8, ofGetHeight() / 8);
            }
        ofPopStyle();
    }
    
    for (int i = 0; i < agentSystem.size(); i++) {
        Agent & selectedAgent = agentSystem.getAgent(i);

        int  x = selectedAgent.getX() * (ofGetWidth() / 8);
        int  y = selectedAgent.getY() * (ofGetHeight() / 8);
        
        ofPushStyle();
            ofSetHexColor(0x92B6B1);
            ofDrawRectangle(x, y, ofGetWidth() / 8, ofGetHeight() / 8);
        ofPopStyle();
    }
}

//--------------------------------------------------------------
void ofApp::audioReceived(float * input, int bufferSize, int nChannels) {
    pd.audioIn(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::audioRequested(float * output, int bufferSize, int nChannels) {
    pd.audioOut(output, bufferSize, nChannels);
}
