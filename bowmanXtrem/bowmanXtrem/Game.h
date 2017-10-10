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

	void restart(sf::Clock& clock);
private:
	ObjectHandler objHandler;
	bool run = true;
	bool reset = false;

	float t = 0;
	float resetT = 0;

	void makeWorld();
};

