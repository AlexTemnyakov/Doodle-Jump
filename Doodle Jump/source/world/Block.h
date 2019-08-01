#ifndef BLOCK_H
#define BLOCK_H

#include <SDL.h>
#include "../texture/Texture.h"

class Block
{
private:
	Texture *texture;
	int x, y, width, height;
public:
	Block(const char* texturePath, int _x, int _y, int w, int h, SDL_Renderer* renderer);
	void render(int yOffset);
};

#endif // !BLOCK_H

