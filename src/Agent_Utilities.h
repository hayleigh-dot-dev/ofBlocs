#pragma once

namespace Agent_Utilities {
	enum Direction {
		UP = 0,
		RIGHT = 1,
		DOWN = 2,
		LEFT = 3
	};

	static int mapTo1d(int x, int y, int width) {
		return width * x + y;
	}

	static int mapXto2d(int x, int width) {
		return x % width;
	}

	static int mapYto2d(int y, int width) {
		return y / width;
	}
}