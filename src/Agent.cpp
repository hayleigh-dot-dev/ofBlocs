#include "Agent.h"

//--------------------------------------------------------------
// Constructor -------------------------------------------------
Agent::Agent(int width, int height) {
    this->width = width;
	this->height = height;
	this->size = width * height;

    grid.resize(size);

    // Place agents in the centre of the grid
    x = width/2;
    y = height/2;
    
	// Give agent a random direction
    d = changeDirection();
}

//--------------------------------------------------------------
// Private Functions -------------------------------------------
void Agent::move() {
    // If a block was placed on an agent
    // place it randomly on the grid 
    if (checkCollision(x, y)) {
        x = (int)ofRandom(this->width);
        y = (int)ofRandom(this->height);
        
        collisionCount = 0;
    }

	// Values used to store the next position based on d
    int newX = x;
	int newY = y;
	switch (d) {
		case Agent_Utilities::UP:
            // Ternary operater quickly handles bounds wrapping
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
        default:
            d = changeDirection(d);
            move();
            break;
	}

	ofLog(OF_LOG_NOTICE, "Agent::move: d = " + ofToString(d));
    ofLog(OF_LOG_NOTICE, "Agent::move: collisionCount = " + ofToString(collisionCount));
    // To avoid potentially selecting infinite invalid new directions
    // a hard cap of 4 attempts is in place, after which the agent is
    // placed randomly elsewhere on the grid
    if (collisionCount >= 4) {
        x = (int)ofRandom(this->width);
        y = (int)ofRandom(this->height);
        
        collisionCount = 0;
        
        move();
    } 
    // Check if the new position collides with a block
    else if (checkCollision(newX, newY)) {
		c = true;
		d = changeDirection(d);
        
        collisionCount++;
        
		// If there is a collision, recursively call move
        move();
	} 
    // If no collision is detected, update x and y with the new position
    else {
		x = newX;
		y = newY;
        
        // Reset collision count
        collisionCount = 0;
	}
}

bool Agent::checkCollision(int x, int y) {
    // 2d - 1d conversion
	int i = width * x + y;
    // See if grid is populated with a block
	bool collision = grid[i];

	return collision;
}

Agent_Utilities::Direction Agent::changeDirection(Agent_Utilities::Direction currentD) {
    // Static define means this array remains through recursive calls
    static Agent_Utilities::Direction a[] = { 
        Agent_Utilities::UP, 
        Agent_Utilities::RIGHT,
        Agent_Utilities::DOWN,
        Agent_Utilities::LEFT
    };
    
	int i = (int)ofRandom(4);
    
    Agent_Utilities::Direction newD = a[i%4];

	// These logs are the remains of testing
    // but agents stop moving when they're taken away...
    ofLog(OF_LOG_NOTICE, "Agent:changeDirection: i = " + ofToString(i));
    ofLog(OF_LOG_NOTICE, "Agent:changeDirection: a[i] = " + ofToString(a[i]));
    
    // If random direction is the same, recursively select another
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
        // Reset the collision variable every update
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
