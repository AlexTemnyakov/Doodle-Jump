#include "game/Game.h"

int main(int argc, char* args[])
{
	Game* game = new Game();
	if (game->init())
		game->run();
	game->stop();
	delete game;
	return 0;
}