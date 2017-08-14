#pragma once

#include "ofMain.h"
#include "Agent_Utilities.h"

class Agent {
private:
	vector<bool>                grid;
    int                         size;
	int							width  = 0;
	int							height = 0;

	int							timer = 0;

	int							x = 0;
	int							y = 0;
	Agent_Utilities::Direction	d;
    int                         collisionCount = 0;
	bool                        c;

	void                        move();

	bool                        checkCollision(int x, int y);
	Agent_Utilities::Direction	changeDirection(Agent_Utilities::Direction currentD);
	Agent_Utilities::Direction	changeDirection();

public:
	Agent(int width, int height);

	void                        update();
	
	void                        resizeGrid(int width, int height);
	void                        updateGrid(int x, int y, bool b);
	void                        updateGrid(int i, bool b);

	bool                        hasCollided();

	int							getX();
	int							getY();
	ofPoint						getPos();
};
