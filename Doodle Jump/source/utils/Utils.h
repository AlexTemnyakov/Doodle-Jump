#pragma once
static class Utils
{
public:
	const char* playersTextureLeftPath = "resources/textures/playerLeft.png";
	const char* playersTextureRightPath = "resources/textures/playerRight.png";
	static const int moveDist = 10;
	static bool fileExists(const char* path);
};

