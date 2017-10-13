#include "Arrow.h"
#include <stdio.h>

Arrow::Arrow(vector pos, vector size, float angle, vector spd) : Obj(pos, size, angle)
{

	this->dir = vector(cos(angle), sin(angle));
	this->pos = pos;
	this->speed = spd;
	this->acc.x = 0.0;
	this->acc.y = GRAVITY;
	this->A = PAJ * 0.395f * 0.395f; //0.395 radie på pilen
	this->inAir = true;
}

Arrow::~Arrow()
{
}

void Arrow::update(float t)
{
	if (inAir)
	{
		//Update arrow position
		this->pos.x = this->pos.x + this->speed.x * t;
		this->pos.y = this->pos.y + this->speed.y * t;

		//Update arrow speed
		this->speed.x = this->speed.x + this->acc.x * t;
		this->speed.y = this->speed.y + this->acc.y * t;

		//Update arrow direction
		this->dir = this->speed.normalize();

		//Update arrow acceleration
		this->acc.x = this->acc.x + (-1.5f) * t;

		//Set arrow position and rotate the texture
		this->shape.setRotation(getAngle());
		this->shape.setPosition(sf::Vector2f(pos.x, pos.y));

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


	/*
	vector pre = pos;

	float a = 0.000001;

	vector res;
	res.x = dir.x * spd;
	res.y = dir.y * spd;

	pos = pos + res;

	pos.y = SCREEN_HEIGHT_MIDDLE + res.y*t + ((a*t*t) / 2);

	this->shape.setRotation(getAngle());
	this->shape.setPosition(sf::Vector2f(pos.x, pos.y));
	*/
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