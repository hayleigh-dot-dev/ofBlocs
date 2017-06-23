#pragma once

#include "ofMain.h"
#include "Agent.h"
#include "Agent_Utilities.h"

class Agent_System {
private:
	int							s;

	vector<Agent>				a;

public:
	Agent_System();

	int							size();
	
	void						addAgent();
	void						removeAgent();
	void						removeAgent(int i);

	Agent &						getAgent(int i);

	void						updateAgent(int i);

	void						resizeAgentGrid(int i, int width, int height);
	void						updateAgentGrid(int i, int x, int y, bool b);
	void						updateAgentGrid(int i, int j, bool b);

	bool						hasAgentCollided(int i);

	int							getAgentX(int i);
	int							getAgentY(int i);
	ofPoint						getAgentPos(int i);
};
