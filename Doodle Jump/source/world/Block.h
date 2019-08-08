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
public:
	Block(const char* texturePath, int _x, int _y, int w, int h, SDL_Renderer* renderer);
	~Block();
	void render(SDL_Renderer* renderer);
	Rectangle getRectangle();
	int getY();
	void setY(int _y);
	int getX();
	int getWidth();
	int getHeight();
};

#endif // !BLOCK_H

