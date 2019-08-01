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
