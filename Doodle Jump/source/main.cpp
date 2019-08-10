#include "game/Game.h"

int main(int argc, char* args[])
{
	Game* game = new Game();
	if (game->init())
		game->run();
	game->stop();
	return 0;
}