#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);

	//----------------------------------------------------------
    // Connect to Arduinos
    serial.listDevices();

	//--------------------------------------------------------------
    // Add Agents
    agentSystem.addAgent();
	agentSystem.addAgent();

    for(int i = 0; i < agentSystem.size(); i++) {
        Agent & selectedAgent = agentSystem.getAgent(i);
        selectedAgent.resizeGrid(5, 5);
        for (int j = 0; j < 25; j++) {
            selectedAgent.updateGrid(j, false);
        }
        selectedAgent.updateGrid(4, 0, true);
        selectedAgent.updateGrid(1, 0, true);
        selectedAgent.updateGrid(0, 4, true);
        selectedAgent.updateGrid(2, 0, true);
        selectedAgent.updateGrid(3, 3, true);
    }

    //--------------------------------------------------------------
    // Setup PureData
    
    // the number of libpd ticks per buffer,
    // used to compute the audio buffer len: tpb * blocksize (always 64)
    #ifdef TARGET_LINUX_ARM
        // longer latency for Raspberry PI
        int ticksPerBuffer = 32; // 32 * 64 = buffer len of 2048
        int numInputs = 0; // no built in mic
    #else
        int ticksPerBuffer = 8; // 8 * 64 = buffer len of 512
        int numInputs = 1;
    #endif
    // setup OF sound stream
    ofSoundStreamSetup(2, numInputs, this, 44100, ofxPd::blockSize()*ticksPerBuffer, 3);
    if(!pd.setup(2, numInputs, 44100, ticksPerBuffer, false)) {
        OF_EXIT_APP(1);
    }
    pd.openPatch("main.pd");
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for(int i = 0; i < agentSystem.size(); i++) {
        agentSystem.updateAgent(i);
        
        if (timer == 0) {
            int  x = agentSystem.getAgentX(i);
            int  y = agentSystem.getAgentY(i);
            bool b = agentSystem.hasAgentCollided(i);
            
            if (b) {
                ofLog(OF_LOG_NOTICE, "Collision detected");
                pd.sendBang("trigger");
            }
            ofLog(OF_LOG_NOTICE, "Agent"+ofToString(i)+" position is: " + ofToString(x) + " : " + ofToString(y));
        }
    }

	timer = ++timer % 60;
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::audioReceived(float * input, int bufferSize, int nChannels) {
    pd.audioIn(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::audioRequested(float * output, int bufferSize, int nChannels) {
    pd.audioOut(output, bufferSize, nChannels);
}
