#include "Game.h"
#include <stdio.h>
#include <thread>
#include "..\time\Timer.h"
using namespace std;

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

	state = MENU;
	changeStateTime = UINT64_MAX;
	changeStateStartTime = 0;

	TTF_Font* font = TTF_OpenFont("resources/fonts/arialbd.ttf", 80);
	SDL_Color color = { 0, 0, 0 };
	menuTextrures[0] = new Texture();
	menuTextrures[0]->loadFromRenderedText("Press \"P\" to play", color, font, window->getRenderer());
	menuTextrures[1] = new Texture();
	menuTextrures[1]->loadFromRenderedText("Press \"Esc\" to quit", color, font, window->getRenderer());

	return ret;
}

void Game::run()
{
	SDL_Event e;
	
	while (!quit)
	{
		switch (state)
		{
		case MENU:
			runMenu();
			break;
		case GAME:
			// start a new game if the player is dead
			if (player == NULL && world == NULL)
			{
				player = new Player("resources/textures/player.png", u.PLAYER_WIDTH, u.PLAYER_HEIGHT, 300, 500, window->getRenderer());
				world = new World(window->getRenderer());
			}
			runGameLoop();
			break;
		}
	}
}

void Game::runMenu()
{
	SDL_Event e;

	Timer t;
	uint64_t lastTime, currentTime, timer, _fps = (uint64_t)fps;
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
			if (currentKeyStates[SDL_SCANCODE_P])
			{
				if (changeStateTime > 1000)
				{
					changeStateTime = 0;
					changeStateStartTime = t.milliseconds();
					state = GAME;
					return;
				}
				else
				{
					changeStateTime = t.milliseconds() - changeStateStartTime;
				}
			}
			if (currentKeyStates[SDL_SCANCODE_ESCAPE])
			{
				quit = true;
			}

			menuTextrures[0]->render(window->getRenderer(), 60, 150);
			menuTextrures[1]->render(window->getRenderer(), 30, 450);

			window->updateScreen();
		}

	}
	window->clearScreen();
}

void Game::runGameLoop()
{
	SDL_Event e;

	Timer t;
	uint64_t lastTime, currentTime, timer, _fps = (uint64_t) fps;
	lastTime = t.nanoseconds();
	while (!quit && player->getY() + player->getHeight() < u.W_HEIGHT)
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

			// get states of the keys
			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			// p button
			if (currentKeyStates[SDL_SCANCODE_P])
			{
				if (changeStateTime > 1000)
				{
					changeStateTime = 0;
					changeStateStartTime = t.milliseconds();
					state = MENU;
					return;
				}
				else
				{
					changeStateTime = t.milliseconds() - changeStateStartTime;
				}
			}
			// button down
			if (currentKeyStates[SDL_SCANCODE_DOWN]) {}
			// button keft
			if (currentKeyStates[SDL_SCANCODE_LEFT])
			{
				player->move(-u.moveDist, 0, world->getBlocks());
			}
			// button right
			if (currentKeyStates[SDL_SCANCODE_RIGHT])
			{
				player->move(u.moveDist, 0, world->getBlocks());
			}
			// space bar
			if (currentKeyStates[SDL_SCANCODE_SPACE]) {/*player->jump(world->getBlocks());*/ }

			world->render(window->getRenderer());
			player->render(window->getRenderer());

			SDL_Color BLACK = { 0, 0, 0 };
			TTF_Font* arialBold50 = TTF_OpenFont("resources/fonts/arialbd.ttf", 50);
			Texture* distanceTexture = new Texture();
			string distanceStr = to_string(player->getTotalDistance());
			distanceTexture->loadFromRenderedText(distanceStr, BLACK, arialBold50, window->getRenderer());
			distanceTexture->render(window->getRenderer(), 10, 10);
			distanceTexture->~Texture();
			TTF_CloseFont(arialBold50);

			window->updateScreen();
		}

	}
	// the player is dead
	window->clearScreen();
	state = MENU;
	player->~Player();
	world->~World();
	player = NULL;
	world = NULL;
}

void Game::stop()
{
	if (player != NULL) player->~Player();
	if (world != NULL) world->~World();
	window->~Window();

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
