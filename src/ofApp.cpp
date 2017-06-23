#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);

	serial.listDevices();

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