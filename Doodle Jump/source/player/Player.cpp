#include "Player.h"
#include "../utils/Utils.h"

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
		dir = true;
	else if (moveX < 0)
		dir = false;
	x += moveX;
	y += moveY;
}
