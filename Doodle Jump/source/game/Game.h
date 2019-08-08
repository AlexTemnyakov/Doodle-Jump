#ifndef GAME_H
#define GAME_H

#include "..\user_interface\Window.h"
#include "..\player\Player.h"
#include "..\utils\Utils.h"
#include "..\world\World.h"

class Game
{
private:
	int fps;
	bool quit;
	Window* window;
	Player* player;
	World* world;
	Utils u;
public:
	Game();
	bool init();
	void run();
	void stop();


};

#endif // !GAME_H

