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

	Agent & selectedAgent = agentSystem.getAgent(0);
	selectedAgent.resizeGrid(5, 5);
	for (int j = 0; j < 25; j++) {
		selectedAgent.updateGrid(j, false);
	}
	selectedAgent.updateGrid(4, 0, true);
	selectedAgent.updateGrid(1, 0, true);
	//selectedAgent.updateGrid(0, 4, true);
    
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
}

//--------------------------------------------------------------
void ofApp::update(){
	agentSystem.updateAgent(0);

	if (timer == 0) {
		int  x = agentSystem.getAgentX(0);
		int  y = agentSystem.getAgentY(0);
		bool b = agentSystem.hasAgentCollided(0);

		if (b) ofLog(OF_LOG_NOTICE, "Collision detected");
		ofLog(OF_LOG_NOTICE, "Agent position is: " + ofToString(x) + " : " + ofToString(y));
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
