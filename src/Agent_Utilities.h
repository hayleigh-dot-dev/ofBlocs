#pragma once

class Agent_Utilities {
public:
	enum Direction {
		UP = 0,
		RIGHT = 1,
		DOWN = 2,
		LEFT = 3
	};

	static int mapTo1d(int x, int y, int width) {
		return width * x + y;
	}
};
