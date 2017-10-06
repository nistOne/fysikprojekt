#include "Fan.h"
#include "Window.h"

Fan::Fan(vector pos, vector size, float angle, float velocity) : Obj(pos, size, angle)
{
	this->velocity = velocity;

	vector vec_up(0.f, -1.f);
	vector vec_right(1.f, 0.f);

	if (this->angle != 0)
	{
		vec_up.rotateLeft(this->angle);
		vec_right.rotateLeft(this->angle);
	}

	area.pos3 = this->pos - vec_right * this->size.x + vec_up * this->size.y;
	area.pos4 = this->pos + vec_right * this->size.x + vec_up * this->size.y;
	
	area.pos1 = area.pos3 + vec_up * 5000;
	area.pos2 = area.pos4 + vec_up * 5000;
}

Fan::~Fan()
{

}

void Fan::drawArea()
{
	sf::ConvexShape aShape;

	aShape.setPointCount(4);

	aShape.setPoint(0, area.pos1.asVector2f());
	aShape.setPoint(1, area.pos2.asVector2f());
	aShape.setPoint(2, area.pos3.asVector2f());
	aShape.setPoint(3, area.pos4.asVector2f());

	gWindow->draw(aShape);
}