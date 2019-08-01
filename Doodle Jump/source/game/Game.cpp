#include "Game.h"
#include <stdio.h>
#include "..\time\Timer.h"
#include "..\utils\Utils.h"

Game::Game()
{
	fps = 60;
	quit = false;
	window = new Window(800, 800);
	player = NULL;
}

bool Game::init()
{
	bool ret = true;

	if (!window->init())
		ret = false;


	player = new Player("resources/textures/player.png", 80, 80, 10, 10, window->getRenderer());

	return ret;
}

void Game::run()
{
	SDL_Event e;
	Utils u;

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

			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			if (currentKeyStates[SDL_SCANCODE_UP])
			{
				printf("Up!\n");
				player->move(0, -u.moveDist);
			}
			if (currentKeyStates[SDL_SCANCODE_DOWN])
			{
				printf("Down!\n");
				player->move(0, u.moveDist);
			}
			if (currentKeyStates[SDL_SCANCODE_LEFT])
			{
				printf("Left!\n");
				player->move(-u.moveDist, 0);
			}
			if (currentKeyStates[SDL_SCANCODE_RIGHT])
			{
				printf("Right!\n");
				player->move(u.moveDist, 0);
			}

			player->render(window->getRenderer());

			window->updateScreen();
		}

	}
}

void Game::stop()
{
	window->~Window();
}
