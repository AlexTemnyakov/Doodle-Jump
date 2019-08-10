#include "Window.h"
#include <stdio.h>
#include <SDL_ttf.h>

Window::Window(int w, int h)
{
	width = w;
	height = h;
}

Window::~Window()
{
	close();
}

bool Window::init()
{
	int ret = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else 
	{
		gWindow = SDL_CreateWindow("Doodle Jump", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		bool ttfRet = (TTF_Init() != -1) ? true : false;
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(gWindow);
		}
		if (gRenderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			ret = false;
		}
		if (!ttfRet)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			ret = false;
		}
	}
	return ret;
}

void Window::clearScreen()
{
	// set white color
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
}

void Window::updateScreen()
{
	SDL_RenderPresent(gRenderer);
}

void Window::close()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
}

SDL_Renderer* Window::getRenderer()
{
	return gRenderer;
}
