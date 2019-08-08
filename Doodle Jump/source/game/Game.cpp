#include "Game.h"
#include <stdio.h>
#include "..\time\Timer.h"

Game::Game()
{
	fps = 60;
	quit = false;
	window = new Window(u.W_WIDTH, u.W_HEIGHT);
	player = NULL;
}

bool Game::init()
{
	bool ret = true;

	if (!window->init())
		ret = false;


	player = new Player("resources/textures/player.png", u.PLAYER_WIDTH, u.PLAYER_HEIGHT, 300, 500, window->getRenderer());
	world = new World(window->getRenderer());

	return ret;
}

void Game::run()
{
	SDL_Event e;

	Timer t;
	uint64_t lastTime, currentTime, timer, _fps = (uint64_t) fps;
	lastTime = t.nanoseconds();
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		currentTime = t.nanoseconds();
		timer = currentTime - lastTime;
		if (timer * _fps > _fps * 10000000) {
			lastTime = currentTime;

			window->clearScreen();

			world->update(window->getRenderer(), player->getY());
			player->update(world->getBlocks());

			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			if (currentKeyStates[SDL_SCANCODE_UP])
			{
				//printf("Up!\n");
				//player->move(0, -u.moveDist, world->getBlocks());
			}
			if (currentKeyStates[SDL_SCANCODE_DOWN])
			{
				//printf("Down!\n");
				player->move(0, u.moveDist, world->getBlocks());
			}
			if (currentKeyStates[SDL_SCANCODE_LEFT])
			{
				//printf("Left!\n");
				player->move(-u.moveDist, 0, world->getBlocks());
			}
			if (currentKeyStates[SDL_SCANCODE_RIGHT])
			{
				//printf("Right!\n");
				player->move(u.moveDist, 0, world->getBlocks());
			}
			if (currentKeyStates[SDL_SCANCODE_SPACE])
			{
				player->jump(world->getBlocks());
			}

			world->render(window->getRenderer());
			player->render(window->getRenderer());

			window->updateScreen();
		}

	}
}

void Game::stop()
{
	window->~Window();
}
