#include "Arrow.h"
#include <stdio.h>


Arrow::Arrow(vector pos, vector size, float angle, vector spd) : Obj(pos, size, angle)
{

	this->dir = vector(cos(angle), sin(angle));
	this->pos = pos;
	if (spd.length() < SPEED_CAP)
		this->speed = spd;
	else
		this->speed = spd.normalize() * SPEED_CAP;

	this->A = PAJ * 0.395 * 0.395; //0.395 radie p� pilen
	this->inAir = true;
	this->Fg = vector(0.f, GRAVITY * this->weight);
	this->Fd = vector(0.f, 0.f);
	this->Ff = vector(0.f, 0.f);

	this->shape.setOrigin(this->size.asVector2f());
	
	//this->tex.loadFromFile("arrow.png", sf::IntRect(8,10, 25, 15));
	//this->tex.setSmooth(true);




}

Arrow::~Arrow()
{
}

float Arrow::getAngle()
{
	vector temp = this->speed - (this->Ff / this->weight);

	return atanf(temp.y / temp.x) * 180.f / PAJ; 
}

void Arrow::update(float t, vector spdWnd)
{
	if (inAir)
	{
		//Update arrow position
		this->pos = this->pos + ((this->speed * t) * SCALE);
		this->shape.setTexture(&tex);
		//Update arrow speed
		this->speed = this->speed + this->acc * t;

		//Update arrow direction
		this->dir = this->speed.normalize();

		//Update arrow acceleration
		this->acc = ((this->Fd + this->Ff + this->Fg) / this->weight);

		//Update arrow forces
		this->Fd = (this->spdRelWind * this->spdRelWind * this->Cd) * (this->dir * (-1));
		this->Ff = spdWnd * this->weight;

		//Update spdRelWind
		this->spdRelWind = this->speed - spdWnd;

		//Set arrow position and rotate the texture
		this->shape.setRotation(getAngle());
		this->shape.setPosition(sf::Vector2f(pos.x, pos.y));

		//Update arrow info text
		this->font.loadFromFile("font.ttf");
		this->arrText.setFont(this->font);
		this->arrText.setCharacterSize(20);
		this->arrText.setColor(sf::Color::Red);
		
		std::string info = "";
		info += "Arrow speed x: " + std::to_string(this->speed.x) + "\n";
		info += "Arrow speed y: " + std::to_string(this->speed.y) + "\n";
		info += "Arrow acc x: " + std::to_string(this->acc.x) + "\n";
		info += "Arrow acc y: " + std::to_string(this->acc.y) + "\n";

		this->arrText.setString(info);
		gWindow->draw(this->arrText);

		/*
		*	Update bounding box
		*/

		vector vec_up(0.f, -1.f);
		vector vec_right(1.f, 0.f);

		vec_up.rotate(getAngle());
		vec_right.rotate(getAngle());

		bbox.pos1 = this->pos - vec_right * this->size.x / 2 + vec_up * this->size.y / 2;
		bbox.pos2 = this->pos + vec_right * this->size.x / 2 + vec_up * this->size.y / 2;
		bbox.pos3 = this->pos - vec_right * this->size.x / 2 - vec_up * this->size.y / 2;
		bbox.pos4 = this->pos + vec_right * this->size.x / 2 - vec_up * this->size.y / 2;
	}
}

bool Arrow::isFlying()
{
	return this->inAir;
}

void Arrow::endFlight()
{
	this->inAir = false;
}

void Arrow::reset()
{
	this->inAir = true;
}

void Arrow::addForceToArrow(vector force)
{

}

vector Arrow::getSpeed()
{
	return this->speed;
}