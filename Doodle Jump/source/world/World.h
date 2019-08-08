#ifndef WORLD_H
#define WORLD_H

#include <iostream> 
#include <set> 
#include <iterator> 
#include "Block.h"
#include "..\utils\Utils.h"
using namespace std;

class World
{
private:
	set <Block*> blocks;
	Utils u;
public:
	World(SDL_Renderer* renderer);
	~World();
	void update(SDL_Renderer* renderer, int playersY);
	void render(SDL_Renderer* renderer);
	set<Block*> getBlocks();
};

#endif // !WORLD_H

