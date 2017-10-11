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

	sf::Clock clock;

	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Red);
	
	while (gWindow->isOpen() && this->run)
	{
		sf::Event event;
		while (gWindow->pollEvent(event))
		{
			if (event.key.code == sf::Keyboard::Escape)
				gWindow->close();

			if (event.key.code == sf::Keyboard::R)
				objHandler.shootArrow(7 * PAJ / 4, vector(100, -50));
		}
		
		this->t = clock.getElapsedTime().asSeconds();

		if (t >= 1.0f / FPS)
		{
			
			gWindow->clear();
			objHandler.update(t);
			objHandler.draw();
			gWindow->display();
			clock.restart();
		}
	}	
}


void Game::restart(sf::Clock& clock)
{
}

void Game::makeWorld()
{
	objHandler.addWall(vector(0, SCREEN_HEIGHT*2/3), vector(SCREEN_WIDTH/2.7, SCREEN_HEIGHT/18), 0);
	objHandler.addWall(vector(SCREEN_WIDTH, SCREEN_HEIGHT * 2 / 3), vector(SCREEN_WIDTH/2.7, SCREEN_HEIGHT / 18), 0);
	objHandler.addWall(vector(SCREEN_WIDTH_MIDDLE, (SCREEN_HEIGHT * 2 / 3) + SCREEN_HEIGHT / 4.5), vector(SCREEN_WIDTH/2, SCREEN_HEIGHT / 5.9), 0);

	objHandler.shootArrow(7*PAJ/4, vector(100, -50));
}
