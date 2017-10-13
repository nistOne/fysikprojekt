#include "Object.h"
#include "Window.h"

Obj::Obj(vector pos, vector size, float angle)
{
	this->pos = pos;
	this->size = size;
	this->angle = angle;

	vector vec_up(0.f, -1.f);
	vector vec_right(1.f, 0.f);

	if (this->angle != 0)
	{
		vec_up.rotate(this->angle);
		vec_right.rotate(this->angle);
	}


	//vector rot = vector((size.x*cos(angle)), (size.y*sin(angle)));
	vector rot = size;

	//bbox.pos1 = this->pos + (vector(-rot.x, -rot.y));
	//bbox.pos2 = this->pos + (vector(rot.x, -rot.y));
	//bbox.pos3 = this->pos + (vector(-rot.x, rot.y));
	//bbox.pos4 = this->pos + (vector(rot.x, rot.y));

	bbox.pos1 = this->pos - vec_right * this->size.x/2 + vec_up * this->size.y/2;
	bbox.pos2 = this->pos + vec_right * this->size.x/2 + vec_up * this->size.y/2;
	bbox.pos3 = this->pos - vec_right * this->size.x/2 - vec_up * this->size.y/2;
	bbox.pos4 = this->pos + vec_right * this->size.x/2 - vec_up * this->size.y/2;

	//shape.setPosition(bbox.pos1.asVector2f());
	shape.setPosition(this->pos.asVector2f());
	shape.setOrigin(this->size.x/2, this->size.y/2);
	shape.setRotation(this->angle);
	shape.setSize(this->size.asVector2f());
	shape.setFillColor(sf::Color::Red);
}

Obj::~Obj()
{

}

void Obj::draw()
{
	gWindow->draw(this->shape);
}

void Obj::update(float t)
{

}