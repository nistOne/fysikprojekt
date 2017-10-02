#include "Game.h"
#include "Window.h"
#include "ObjectHandler.h"

Game::Game()
{
	gWindow = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");
}

Game::~Game()
{
	delete gWindow;
}

void Game::gameLoop()
{
	ObjectHandler objHandler;

	objHandler.addWall(vector(100, 100), vector(50, 50), 0);

	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Red);

	while (gWindow->isOpen() && this->run)
	{
		sf::Event event;
		while (gWindow->pollEvent(event))
		{
			if (event.key.code == sf::Keyboard::Escape)
				gWindow->close();

			//if (event.type == sf::Event::Closed)
			//	gWindow->close();
		}

		gWindow->clear();
		objHandler.draw();
		gWindow->display();
	}	
}


void Game::restart()
{

}