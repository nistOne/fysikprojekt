#include "Arrow.h"

Arrow::Arrow(vector pos, vector size, float angle, float spd) : Obj(pos, size, angle)
{

	dir = vector(pos.x*cos(angle), pos.y*sin(angle));
	this->pos = pos;
	this->spd = spd;
}

Arrow::~Arrow()
{
}

void Arrow::update()
{
	vector res;
	res.x = dir.x;
	res.y = dir.y;

	pos.add(res);

	this->shape.setRotation(getAngle());
	this->shape.setPosition(sf::Vector2f(pos.x, pos.y));
}
