#ifndef GAME_H
#define GAME_H

#include "..\user_interface\Window.h"
#include "..\player\Player.h"
#include "..\utils\Utils.h"
#include "..\world\World.h"

typedef enum {
	MENU,
	GAME
} GameState;

class Game
{
private:
	int fps;
	bool quit;
	Window* window;
	Player* player;
	World* world;
	GameState state;
	// to avoid that changing of the state is too often
	unsigned long changeStateTime, changeStateStartTime;
	Texture* menuTextrures[2];
	Utils u;
	void runMenu();
	void runGameLoop();
public:
	Game();
	bool init();
	void run();
	void stop();


};

#endif // !GAME_H

