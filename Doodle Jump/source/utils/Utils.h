#pragma once
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

	// dimension of the window
	const int W_WIDTH = 800, W_HEIGHT = 800;
	static bool fileExists(const char* path);
};

