#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "..\texture\Texture.h"
#include "..\utils\Utils.h"
#include "..\time\Timer.h"

class Player
{
private:
	Texture *textureLeft, *textureRight;
	int width, height, x, y;
	// false - left, true - right
	bool dir;
	// calculating of free fall
	int speed = 0;
	long lastTime = 0;
	Utils u;
	Timer t;
public:
	Player(const char* texturePath, int w, int h, int x, int y, SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);
	void move(int moveX, int moveY);
	void update();
};

#endif // !PLAYER_H

