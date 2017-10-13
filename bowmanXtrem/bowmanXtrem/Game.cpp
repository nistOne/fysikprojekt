#include "Game.h"
#include "Window.h"

#include <iostream>

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
	//debug_fan();

	sf::Clock clock;

	
	while (gWindow->isOpen() && this->run)
	{
		sf::Event event;
		while (gWindow->pollEvent(event))
		{
			//if (event.key.code == sf::Keyboard::Escape)
			//	gWindow->close();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (!aim)
				{
				aim = true;
				this->firstAim = vector(mouseX, mouseY); 
				}

				vector shootVector = (vector(mouseX, mouseY) - this->firstAim);
				objHandler.updateAimLine(firstAim, shootVector)
			}
			else if (aim)
			{
				this->secondAim = vector(mouseX, mouseY);
				vector shootVector = (this->secondAim - this->firstAim);
				objHandler.shootArrow(shootVector.angle(), shootVector.scale(1.0f));
				aim = false;
			}

			if (event.key.code == sf::Keyboard::R)
				objHandler.shootArrow(7 * PAJ / 4, vector(100, -50));
			if (event.type == sf::Event::Closed)
				gWindow->close();
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
	objHandler.addWall(vector(0.f, SCREEN_HEIGHT*2.f/3.f), vector(SCREEN_WIDTH/2.7f, SCREEN_HEIGHT/18.f), 0.f);
	objHandler.addWall(vector(SCREEN_WIDTH, SCREEN_HEIGHT * 2.f / 3.f), vector(SCREEN_WIDTH/2.7f, SCREEN_HEIGHT / 18.f), 0.f);
	objHandler.addWall(vector(SCREEN_WIDTH_MIDDLE, (SCREEN_HEIGHT * 2.f / 3.f) + SCREEN_HEIGHT / 4.5f), vector(SCREEN_WIDTH/2.f, SCREEN_HEIGHT / 5.9f), 0.f);

	objHandler.shootArrow(7.f*PAJ/4.f, SPEED);
}

void Game::debug_fan()
{
	objHandler.addFan(vector(SCREEN_WIDTH/4.f, SCREEN_HEIGHT*3.f/4.f), vector(150.f, 20.f), 15.f, 50.f);
}
