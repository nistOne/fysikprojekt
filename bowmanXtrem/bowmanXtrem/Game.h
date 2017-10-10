#pragma once
#include "Globals.h"
#include "ObjectHandler.h"

#define FPS 60

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

	float t = 0;

	void makeWorld();
};

