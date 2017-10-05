#include "Arrow.h"
#include <stdio.h>

Arrow::Arrow(vector pos, vector size, float angle, float spd) : Obj(pos, size, angle)
{

	dir = vector(cos(angle), sin(angle));
	this->pos = pos;
	this->spd = spd;
}

Arrow::~Arrow()
{
}

void Arrow::update(int t)
{
	vector pre = pos;

	float a = 0.000001;

	vector res;
	res.x = dir.x * spd;
	res.y = dir.y * spd;

	pos = pos.add(res);

	pos.y = SCREEN_HEIGHT_MIDDLE + res.y*t + ((a*t*t) / 2);

	this->shape.setRotation(getAngle());
	this->shape.setPosition(sf::Vector2f(pos.x, pos.y));
}
