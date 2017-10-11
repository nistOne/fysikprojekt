#include "ObjectHandler.h"
#include "Wall.h"
#include "Arrow.h"

ObjectHandler::ObjectHandler()
{
}

ObjectHandler::~ObjectHandler()
{
}

void ObjectHandler::draw()
{
	for (int i = 0; i < statObjects.size(); i++)
	{
		statObjects.at(i).draw();
	}

	for (int i = 0; i < dynObjects.size(); i++)
	{
		dynObjects.at(i).draw();
	}
}

void ObjectHandler::update(float t)
{
	Arrow* temp = dynamic_cast<Arrow*>(&dynObjects.at(0));
	if (temp != nullptr)
	{
		temp->update(t);
	}
	for (int i = 0; i < dynObjects.size(); i++)
	{
		dynObjects.at(i).update(t);
	}

}

void ObjectHandler::addWall(vector pos, vector size, float angle)
{
	statObjects.push_back(Wall(pos, size, angle));
}

void ObjectHandler::shootArrow(float angle, vector spd)
{
	if(dynObjects.size() > 0)
		dynObjects.pop_back();
	dynObjects.push_back(Arrow(vector(10, SCREEN_HEIGHT/2), vector(20,2), angle, spd));

}
