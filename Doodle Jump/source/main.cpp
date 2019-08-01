/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/
#include <stdio.h>
#include "game/Game.h"

int main(int argc, char* args[])
{
	Game* game = new Game();
	if (game->init())
		game->run();
	game->stop();

	return 0;
}