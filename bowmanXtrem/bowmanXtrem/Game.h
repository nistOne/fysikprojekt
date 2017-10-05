#pragma once
#include "Globals.h"
#include "ObjectHandler.h"

class Game
{
public:
	Game();
	~Game();

	void gameLoop();
	void stopLoop() { this->run = false; };

	void restart();
private:
	ObjectHandler objHandler;
	bool run = true;

	int t = 0;

	void makeWorld();
};

