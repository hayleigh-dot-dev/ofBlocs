#include "Agent.h"

//--------------------------------------------------------------
// Constructor -------------------------------------------------
Agent::Agent(int width, int height) {
    this->width = width;
	this->height = height;
	this->size = width * height;

    grid.resize(size);

    x = width/2;
    y = height/2;
    
	d = changeDirection();
}

//--------------------------------------------------------------
// Private Functions -------------------------------------------
void Agent::move() {
    if (checkCollision(x, y)) {
        x = (int)ofRandom(this->width);
        y = (int)ofRandom(this->height);
        
        collisionCount = 0;
        
        move();
    }

	int newX = x;
	int newY = y;
	switch (d) {
		case Agent_Utilities::UP:
			y - 1 < 0 ? newY = height - 1 : newY = y - 1;
			break;
		case Agent_Utilities::RIGHT:
			newX = (x + 1) % width;
			break;
		case Agent_Utilities::DOWN:
			newY = (y + 1) % height;
			break;
		case Agent_Utilities::LEFT:
			x - 1 < 0 ? newX = width - 1 : newX = x - 1;
			break;
	}

	ofLog(OF_LOG_NOTICE, "Agent::move: d = " + ofToString(d));
    ofLog(OF_LOG_NOTICE, "Agent::move: collisionCount = " + ofToString(collisionCount));
    if (collisionCount >= 4) {
        x = (int)ofRandom(this->width);
        y = (int)ofRandom(this->height);
        
        collisionCount = 0;
        
        move();
    } else if (checkCollision(newX, newY)) {
		c = true;
		d = changeDirection(d);
        
        collisionCount++;
        
		move();
	} else {
		x = newX;
		y = newY;
        
        collisionCount = 0;
	}
}

bool Agent::checkCollision(int x, int y) {
	int i = width * x + y;
	bool collision = grid[i];

	return collision;
}

Agent_Utilities::Direction Agent::changeDirection(Agent_Utilities::Direction currentD) {
    static Agent_Utilities::Direction a[] = { 
        Agent_Utilities::UP, 
        Agent_Utilities::RIGHT,
        Agent_Utilities::DOWN,
        Agent_Utilities::LEFT
    };
    
	int i = (int)ofRandom(4);
    
    Agent_Utilities::Direction newD = a[i];

	// These logs are the remains of testing
    // but agents stop moving when they're taken away...
    ofLog(OF_LOG_NOTICE, "Agent:changeDirection: i = " + ofToString(i));
    ofLog(OF_LOG_NOTICE, "Agent:changeDirection: a[i] = " + ofToString(a[i]));
    
    if (newD == currentD) {
		changeDirection(currentD);
	}
	else {
		return newD;
	}
}

Agent_Utilities::Direction Agent::changeDirection() {
	int a[] = { 0, 1, 2, 3 };
	int i = (int)ofRandom(4);

	return (Agent_Utilities::Direction)a[i];
}

//--------------------------------------------------------------
// Public Functions --------------------------------------------
void Agent::update() {
    if (size > 0) {
        c = false;

        move();
    }
}

//--------------------------------------------------------------
void Agent::resizeGrid(int width, int height) {
	this->width = width;
	this->height = height;
	this->size = width * height;

    grid.resize(size);
}

void Agent::updateGrid(int x, int y, bool b) {
	if (x < 0) {
		ofLog(OF_LOG_WARNING, "Agent::updateGrid: X value below 0, taking absolute value.");
	}
	if (y < 0) {
		ofLog(OF_LOG_WARNING, "Agent::updateGrid: Y value below 0, taking absolute value.");
	}

	int i = Agent_Utilities::mapTo1d(abs(x), abs(y), width);

	if (i >= size) {
		ofLog(OF_LOG_WARNING, "Agent::updateGrid: Index out of bounds, wrapping to vector size.");
	}

	grid[i % size] = b;
}

void Agent::updateGrid(int i, bool b) {
	if (i >= size) {
		ofLog(OF_LOG_WARNING, "Agent::updateGrid: Index out of bounds, wrapping to vector size.");
	}

	grid[i % size] = b;
}

//--------------------------------------------------------------
bool Agent::hasCollided() {
	return c;
}

//--------------------------------------------------------------
int Agent::getX() {
	return x;
}

int Agent::getY() {
	return y;
}

ofPoint Agent::getPos() {
	return ofPoint(x, y);
}
