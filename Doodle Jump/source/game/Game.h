#ifndef GAME_H
#define GAME_H

#include "..\user_interface\Window.h"
#include "..\player\Player.h"

class Game
{
private:
	int fps;
	bool quit;
	Window* window;
	Player* player;
public:
	Game();
	bool init();
	void run();
	void stop();


};

#endif // !GAME_H

