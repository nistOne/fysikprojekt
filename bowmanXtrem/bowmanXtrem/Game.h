#pragma once
#include "Globals.h"

class Game
{
public:
	Game();
	~Game();

	void gameLoop();
	void stopLoop() { this->run = false; };

	void restart();
	
private:

	bool run = true;


};

