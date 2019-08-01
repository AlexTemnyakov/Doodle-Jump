#include "Player.h"

Player::Player(const char* texturePath, int w, int h, int _x, int _y, SDL_Renderer* renderer)
{
	Utils u;
	textureLeft = new Texture(u.playersTextureLeftPath, w, h, renderer);
	textureRight = new Texture(u.playersTextureRightPath, w, h, renderer);
	width = w;
	height = h;
	x = _x;
	y = _y;
	dir = true;
}

void Player::render(SDL_Renderer* renderer)
{
	if (dir) 
		textureRight->render(renderer, x, y);
	else
		textureLeft->render(renderer, x, y);
}

void Player::move(int moveX, int moveY)
{
	if (moveX > 0)
	{
		dir = true;
		if (x + width + moveX < u.W_WIDTH)
			x += moveX;
		else
			x = u.W_WIDTH - width;
	}
	else if (moveX < 0)
	{
		dir = false;
		if (x + moveX > 0)
			x += moveX;
		else
			x = 0;
	}

	if (moveY < 0)
	{
		if (y + moveY > 0)
			y += moveY;
		else
			y = 0;
	}
	else
	{
		y += moveY;
	}
}

void Player::update()
{
	/*long time = (t.nanoseconds()) / 1E9;
	long dt = time - lastTime;
	lastTime = time;
	speed += 10 * dt;
	y += 0.5 * speed * dt;
	printf("y=%d speed=%d dt=%d\n", y, speed, dt);*/
}
