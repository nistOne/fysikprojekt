#include "Wall.h"

Wall::Wall(vector pos, vector size, float angle) : Obj(pos, size, angle)
{
	this->color = sf::Color::White;
	this->shape.setFillColor(this->color);
}

Wall::~Wall()
{
}