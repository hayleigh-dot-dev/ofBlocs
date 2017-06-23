#include "Agent.h"

//--------------------------------------------------------------
// Constructor -------------------------------------------------
Agent::Agent() {
	d = changeDirection();
}

//--------------------------------------------------------------
// Private Functions -------------------------------------------
void Agent::move() {
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

	if (checkCollision(newX, newY)) {
		c = true;
		d = changeDirection(d);

		move();
	}
	else {
		x = newX;
		y = newY;
	}
}

bool Agent::checkCollision(int x, int y) {
	bool collision = false;
	int i = Agent_Utilities::mapTo1d(x, y, width);

	collision = grid[i];

	return collision;
}

Agent_Utilities::Direction Agent::changeDirection(Agent_Utilities::Direction currentD) {
	int a[] = { 0, 1, 2, 3 };
	int i = rand() % 4;

	if ((Agent_Utilities::Direction)a[i] == currentD) {
		changeDirection(currentD);
	}
	else {
		return (Agent_Utilities::Direction)a[i];
	}
}

Agent_Utilities::Direction Agent::changeDirection() {
	int a[] = { 0, 1, 2, 3 };
	int i = rand() % 4;

	return (Agent_Utilities::Direction)a[i];
}

//--------------------------------------------------------------
// Public Functions --------------------------------------------
void Agent::update() {
	if (timer == 0) {
		if (grid.size() > 0) {
			c = false;

			move();
		}
	}

	timer = ++timer % 60;
}

//--------------------------------------------------------------
void Agent::resizeGrid(int width, int height) {
	this->width = width;
	this->height = height;
	int size = width * height;

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

	if (i >= grid.size()) {
		ofLog(OF_LOG_WARNING, "Agent::updateGrid: Index out of bounds, wrapping to vector size.");
	}

	grid[i % grid.size()] = b;
}

void Agent::updateGrid(int i, bool b) {
	if (i >= grid.size()) {
		ofLog(OF_LOG_WARNING, "Agent::updateGrid: Index out of bounds, wrapping to vector size.");
	}

	grid[i % grid.size()] = b;
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
