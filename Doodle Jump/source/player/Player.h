#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "..\texture\Texture.h"

class Player
{
private:
	Texture *textureLeft, *textureRight;
	int width, height, x, y;
	// false - left, true - right
	bool dir;
public:
	Player(const char* texturePath, int w, int h, int x, int y, SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);
	void move(int moveX, int moveY);
};

#endif // !PLAYER_H

