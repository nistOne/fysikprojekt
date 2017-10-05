#include "Game.h"
#include "Window.h"

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

	makeWorld();

	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Red);

	while (gWindow->isOpen() && this->run)
	{
		sf::Event event;
		while (gWindow->pollEvent(event))
		{
			if (event.key.code == sf::Keyboard::Escape)
				gWindow->close();

			//if (event.type == sf::event::closed)
			//	gwindow->close();
		}

		gWindow->clear();
		objHandler.update();
		objHandler.draw();
		gWindow->display();
	}	
}


void Game::restart()
{

}

void Game::makeWorld()
{
	objHandler.addWall(vector(0, SCREEN_HEIGHT*2/3), vector(SCREEN_WIDTH/2.7, SCREEN_HEIGHT/18), 0);
	objHandler.addWall(vector(SCREEN_WIDTH, SCREEN_HEIGHT * 2 / 3), vector(SCREEN_WIDTH/2.7, SCREEN_HEIGHT / 18), 0);
	objHandler.addWall(vector(SCREEN_WIDTH_MIDDLE, (SCREEN_HEIGHT * 2 / 3) + SCREEN_HEIGHT / 4.5), vector(SCREEN_WIDTH/2, SCREEN_HEIGHT / 5.9), 0);

	objHandler.shootArrow(-45,0.5);
}
