#include "Wall.h"

Wall::Wall(vector pos, vector size, float angle) : Obj(pos, size, angle)
{
	this->color = sf::Color::Yellow;
	this->shape.setFillColor(this->color);
}

Wall::~Wall()
{
}

void Wall::editLine(vector pos, vector line)
{
	this->color = sf::Color::White;
	this->pos = pos;
	this->angle = line.angle();
	this->size.x = line.length();

	this->shape.setOrigin((size*1.0f).asVector2f());
	this->shape.setSize(this->size.asVector2f());
	this->shape.setRotation(this->angle);
	this->shape.setPosition(this->pos.asVector2f());
	this->shape.setFillColor(this->color);
}

void Wall::setColor(sf::Color newColor)
{
	this->shape.setFillColor(newColor);
}

