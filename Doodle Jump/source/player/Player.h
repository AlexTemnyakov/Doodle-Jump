#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <set>
#include "..\texture\Texture.h"
#include "..\utils\Utils.h"
#include "..\time\Timer.h"
#include "..\world\Block.h"
#include "..\world\World.h"

class Player
{
private:
	Texture *textureLeft, *textureRight;
	int width, height, x, y;
	// false - left, true - right
	bool dir;
	// calculating of free fall
	double speed = 0;
	double lastTime = 0;
	// for jumping
	bool jumping = false;
	int jumpDist = 0;
	long jumpTimer = 0;
	int jumpTotalTime = 0;
	// ---
	int totalDistCurrent;
	int totalDistMax;
	// utilities
	Utils u;
	Timer t;
public:
	Player(const char* texturePath, int w, int h, int x, int y, SDL_Renderer* renderer);
	~Player();
	void render(SDL_Renderer* renderer);
	void move(int moveX, int moveY, set<Block*> blocks);
	void update(set<Block*> blocks);
	void jump(set<Block*> blocks);
	Rectangle getRectangle();
	int getY();
	int getX();
	int getWidth();
	int getHeight();
	int getTotalDistance();
};

#endif // !PLAYER_H

