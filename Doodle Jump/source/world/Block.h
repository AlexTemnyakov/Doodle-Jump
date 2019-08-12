#ifndef BLOCK_H
#define BLOCK_H

#include <SDL.h>
#include "../texture/Texture.h"
#include "../utils/Utils.h"

class Block
{
private:
	Texture *texture;
	int x, y, width, height;
	bool breakable;
	bool touched = false;
public:
	Block(const char* texturePath, int _x, int _y, int w, int h, SDL_Renderer* renderer, bool _breakable = false);
	~Block();
	void render(SDL_Renderer* renderer);
	Rectangle getRectangle();
	int getY();
	void setY(int _y);
	int getX();
	int getWidth();
	int getHeight();
	bool isBreakable();
	bool isTouched();
	void setTouched();
};

#endif // !BLOCK_H

