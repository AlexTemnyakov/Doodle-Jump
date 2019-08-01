#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>

class Window
{
private:
	int width, height;
	SDL_Window* gWindow = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Renderer* gRenderer = NULL;
public:
	Window(int w, int h);
	~Window();
	bool init();
	void clearScreen();
	void updateScreen();
	void close();
	SDL_Renderer* getRenderer();
};

#endif // !WINDOW_H

