#pragma once

struct Rectangle
{
	int x;
	int y;
	int width;
	int height;
};

bool valueInRange(int value, int min, int max);

bool rectOverlap(Rectangle A, Rectangle B);

static class Utils
{
public:
	// texture paths
	const char* playersTextureLeftPath = "resources/textures/playerLeft.png";
	const char* playersTextureRightPath = "resources/textures/playerRight.png";
	const char* blockTexturePath = "resources/textures/block.png";

	// player's data
	const int moveDist = 10;
	const int PLAYER_WIDTH = 80, PLAYER_HEIGHT = 80;

	// physics
	// free fall acceleration, pixel per millisecond
	const double g = 0.037936;

	// world's data
	const int BLOCK_WIDTH = 100, BLOCK_HEIGHT = 50;

	// dimension of the window
	const int W_WIDTH = 800, W_HEIGHT = 800;

	static bool fileExists(const char* path);
};

