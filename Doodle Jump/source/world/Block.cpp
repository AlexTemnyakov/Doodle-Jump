#include "Block.h"
#include "../utils/Utils.h"

Block::Block(const char* texturePath, int _x, int _y, int w, int h, SDL_Renderer* renderer)
{
	Utils u;
	texture = new Texture(u.blockTexturePath, w, h, renderer);
	x = _x;
	y = _y;
	width = w;
	height = h;
}

Block::~Block()
{
	texture->~Texture();
}

void Block::render(SDL_Renderer* renderer)
{
	texture->render(renderer, x, y);
}

Rectangle Block::getRectangle()
{
	Rectangle r = { x, y, width, height };
	return r;
}

int Block::getY()
{
	return y;
}

void Block::setY(int _y)
{
	y = _y;
}

int Block::getX()
{
	return x;
}

int Block::getWidth()
{
	return width;
}

int Block::getHeight()
{
	return height;
}
