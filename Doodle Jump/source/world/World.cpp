#include "World.h"
#include <cstdlib>
#include <time.h>

World::World(SDL_Renderer* renderer)
{
	blocks.insert(new Block("resources/textures/block.png", 300, 660, 100, 50, renderer));
	blocks.insert(new Block("resources/textures/block.png", 50, 580, 100, 50, renderer));
	blocks.insert(new Block("resources/textures/block.png", 400, 480, 100, 50, renderer));
	blocks.insert(new Block("resources/textures/block.png", 200, 350, 100, 50, renderer));
	blocks.insert(new Block("resources/textures/block.png", 20, 140, 100, 50, renderer));
	for (auto b : blocks)
	{
		//printf("Blocks --> %d %d\n", b->getRectangle().x, b->getRectangle().width);
	}
	

	srand(time(NULL));
}

World::~World()
{
	for (Block* b : blocks)
	{
		b->~Block();
	}
}

void World::update(SDL_Renderer* renderer, int playersY)
{
	// if the player if above 1/3 part of the window, shift the game world
	if (playersY > u.W_HEIGHT / 3)
		return;

	// delete blocks that are breakable and have been touched by the player
	std::set<Block*>::iterator it = blocks.begin();
	while (it != blocks.end())
	{
		Block* b = *it;
		if (b->isTouched() && b->isBreakable())
		{
			Block* _b = b;
			it = blocks.erase(it);
			_b->~Block();
		}
		else
		{
			it++;
		}
	}

	bool blockInRange = false;
	// if there is no block near, create new one
	for (auto b : blocks)
	{
		if (valueInRange(0, b->getY() - 200, b->getY() + u.BLOCK_HEIGHT + 200))
		{
			blockInRange = true;
			break;
		}
	}
	if (!blockInRange)
	{
		// create a block that doesn't interesect with other blocks
		while (true)
		{
			int xNew = rand() % (u.W_WIDTH - u.BLOCK_WIDTH);
			if (xNew < u.PLAYER_WIDTH || xNew + u.BLOCK_WIDTH > u.W_WIDTH - u.PLAYER_WIDTH)
				continue;
			Rectangle r = { xNew, 0, u.BLOCK_WIDTH, u.BLOCK_HEIGHT };
			bool overlap = false;
			for (auto b : blocks)
			{
				Rectangle bRect = { b->getX(), b->getY(), u.BLOCK_WIDTH, u.BLOCK_HEIGHT };
				if (rectOverlap(r, bRect))
				{
					overlap = true;
					break;
				}
			}

			if (!overlap)
			{
				int breakAblePercentage = rand() % 100;
				bool breakable;
				if (breakAblePercentage < 80)
					breakable = false;
				else
					breakable = true;
				blocks.insert(new Block("resources/textures/block.png", xNew, -50, 100, 50, renderer, breakable));
				break;
			}
		}
	}

	it = blocks.begin();
	// shift blocks and delete them, if they are out of the game world
	while (it != blocks.end())
	{
		Block* b = *it;
		b->setY(b->getY() + 8);
		if (b->getY() > u.W_HEIGHT)
		{
			Block* _b = b;
			it = blocks.erase(it);
			_b->~Block();
		}
		else
		{
			it++;
		}
	}
}

void World::render(SDL_Renderer* renderer)
{
	for (Block* b : blocks)
	{
		b->render(renderer);
	}
}

set<Block*> World::getBlocks()
{
	return blocks;
}
