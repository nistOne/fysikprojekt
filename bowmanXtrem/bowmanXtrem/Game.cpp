#include "Game.h"
#include "Window.h"

#include <iostream>
#include <sstream>

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

	sf::Text arrText;
	sf::Font font;
	font.loadFromFile("font.ttf");
	arrText.setFont(font);
	arrText.setCharacterSize(20);
	arrText.setColor(sf::Color::Red);
	std::string arrSpeed;
	//arrText.setStyle();

	sf::Clock clock;

	
	while (gWindow->isOpen() && this->run)
	{
		sf::Event event;
		while (gWindow->pollEvent(event))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				vector mousePos = vector(sf::Mouse::getPosition(*gWindow).x, sf::Mouse::getPosition(*gWindow).y);
				if (this->aim == false)
				{
				aim = true;
				this->firstAim = mousePos;
				}

				vector shootVector = (this->firstAim - mousePos);
				if (shootVector.length() > 10)
					objHandler.updateAimLine(firstAim, shootVector);
			}
			else if (aim)
			{
				this->secondAim = vector(sf::Mouse::getPosition(*gWindow).x, sf::Mouse::getPosition(*gWindow).y);
				vector shootVector = (this->firstAim - this->secondAim);
				objHandler.shootArrow(shootVector.angle(), shootVector); // .scale(1.0f));
				objHandler.updateAimLine(vector(0,0), vector(0, 0));
				aim = false;
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			{
				objHandler.shootArrow(7 * PAJ / 4, vector(30, -20));
				objHandler.reset();
			}

			if (event.type == sf::Event::Closed)
				gWindow->close();
			if (event.key.code == sf::Keyboard::Escape)
				gWindow->close();
		}
		
		this->t = clock.getElapsedTime().asSeconds();

		if (t >= 1.0f / FPS)
		{
			
			gWindow->clear();
			int results = objHandler.update(t);
			if (results)
			{
				this->stage = results;
				this->makeWorld();
			}
			objHandler.draw(this->aim);
			arrSpeed = getArrowSpeed();
			arrText.setString(arrSpeed);
			gWindow->draw(arrText);
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
	objHandler.clear();

	switch (stage)
	{
	case 0:
		/*Target*/
		objHandler.addTarget(vector(SCREEN_WIDTH * 0.9f, SCREEN_HEIGHT * 2.f / 3.2f), vector(SCREEN_WIDTH / 25.f, SCREEN_HEIGHT / 20.f), 45.f);

		/*Walls*/
		objHandler.addWall(vector(0.f, SCREEN_HEIGHT*2.f / 3.f), vector(SCREEN_WIDTH / 2.7f, SCREEN_HEIGHT / 18.f), 0.f);
		objHandler.addWall(vector(SCREEN_WIDTH, SCREEN_HEIGHT * 2.f / 3.f), vector(SCREEN_WIDTH / 2.7f, SCREEN_HEIGHT / 18.f), 0.f);
		objHandler.addWall(vector(SCREEN_WIDTH_MIDDLE, (SCREEN_HEIGHT * 2.f / 3.f) + SCREEN_HEIGHT / 4.5f), vector(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 5.9f), 0.f);

		/*Fans*/
		objHandler.addFan(vector(SCREEN_WIDTH_MIDDLE, (SCREEN_HEIGHT * 2.f / 3.f) + SCREEN_HEIGHT / 4.5f), vector(60.f, 10.f), 0.f, 70.f);
		objHandler.addFan(vector(SCREEN_WIDTH_MIDDLE - 200, 100), vector(60.f, 10.f), 160.f, 30.f);
		break;
	case 1:
		/*Target*/
		objHandler.addTarget(vector(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 2.f / 3.2f), vector(SCREEN_WIDTH / 25.f, SCREEN_HEIGHT / 7.f), 115.f);

		/*Walls*/
		objHandler.addWall(vector(SCREEN_WIDTH_MIDDLE, 0), vector(SCREEN_WIDTH * 0.05f, SCREEN_HEIGHT * 1.5f), 0.f);

		/*Fans*/
		objHandler.addFan(vector(SCREEN_WIDTH_MIDDLE, (SCREEN_HEIGHT - 10.f) + SCREEN_HEIGHT / 4.5f), vector(60.f, 10.f), 0.f, 270.f);
		
		break;
	default:
		break;
	}
	
	/* World Wind */
	//objHandler.addFan(vector(-10.f, SCREEN_HEIGHT_MIDDLE), vector(SCREEN_HEIGHT, 0), 90.f, 10.f);

	/*Default arrow, for debuging*/
	objHandler.shootArrow(7.f*PAJ/4.f, vector(100, -50));
}

void Game::debug_fan()
{
	objHandler.addFan(vector(SCREEN_WIDTH/4.f, SCREEN_HEIGHT*3.f/4.f), vector(150.f, 20.f), 15.f, 10.f);
}

std::string Game::getArrowSpeed()
{
	std::string text;
	vector speed = this->objHandler.getArrowSpeed();
	std::ostringstream buff; 
	std::ostringstream buff2;
	buff << speed.x;
	text += "Arrow speed x: " + buff.str() + "\n";
	buff2 << speed.y;
	text += "Arrow speed y: " + buff2.str() + "\n";

	return text;
}