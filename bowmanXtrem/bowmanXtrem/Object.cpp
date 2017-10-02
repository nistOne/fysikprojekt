#include "Object.h"
#include "Window.h"

Obj::Obj(vector pos, vector size, float angle)
{
	this->pos = pos;
	this->size = size;


	//vector rot = vector((size.x*cos(angle)), (size.y*sin(angle)));
	vector rot = size;

	bbox.pos1 = pos.add(vector(-rot.x, -rot.y));
	bbox.pos2 = pos.add(vector(rot.x, -rot.y));
	bbox.pos3 = pos.add(vector(-rot.x, rot.y));
	bbox.pos4 = pos.add(vector(rot.x, rot.y));

	this->shape.setPosition(sf::Vector2f(bbox.pos1.x, bbox.pos1.y));

	this->shape.setSize(sf::Vector2f(2*size.x, 2*size.y));
}

Obj::~Obj()
{
}

void Obj::draw()
{
	gWindow->draw(this->shape);
}

void Obj::setRenderTarget(sf::RenderTarget * window)
{

}