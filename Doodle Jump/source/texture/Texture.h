#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class Texture
{
private:
	SDL_Texture* texture;
	int width, height;
public:
	Texture(const char* path, SDL_Renderer* renderer);
	Texture(const char* path, int w, int h, SDL_Renderer* renderer);
	~Texture();
	void loadFromFile(std::string path, SDL_Renderer* renderer);
	void loadFromFile(const char* path, SDL_Renderer* renderer);
	void free();
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point * center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
};

#endif // !TEXTURE_H

