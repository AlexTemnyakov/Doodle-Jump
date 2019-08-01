#include "Window.h"
#include <stdio.h>

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
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else if (gRenderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return ret;
}

void Window::clearScreen()
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
}

void Window::updateScreen()
{
	SDL_RenderPresent(gRenderer);
}

void Window::close()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	SDL_Quit();
}

SDL_Renderer* Window::getRenderer()
{
	return gRenderer;
}
