#include "Block.h"
#include "../utils/Utils.h"

Block::Block(const char* texturePath, int _x, int _y, int w, int h, SDL_Renderer* renderer, bool _breakable)
{
	Utils u;
	if (_breakable)
		texture = new Texture(u.blockBreakableTexturePath, w, h, renderer);
	else
		texture = new Texture(u.blockTexturePath, w, h, renderer);
	x = _x;
	y = _y;
	width = w;
	height = h;
	breakable = _breakable;
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

bool Block::isBreakable()
{
	return breakable;
}

bool Block::isTouched()
{
	return touched;
}

void Block::setTouched()
{
	touched = true;
}
