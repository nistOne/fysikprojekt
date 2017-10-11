#include "ObjectHandler.h"
#include "Wall.h"
#include "Arrow.h"
#include "Fan.h"

ObjectHandler::ObjectHandler()
{
}

ObjectHandler::~ObjectHandler()
{
}

void ObjectHandler::draw()
{
	for (unsigned int i = 0; i < statObjects.size(); i++)
	{
		statObjects.at(i).draw();
	}

	for (unsigned int i = 0; i < arrows.size(); i++)
	{
		arrows.at(i).draw();
	}

	for (unsigned int i = 0; i < fans.size(); i++)
	{
		fans[i].draw();

	}
}

void ObjectHandler::update(float t)
{
	Arrow* temp = dynamic_cast<Arrow*>(&arrows.at(0));
	if (temp != nullptr)
	{
		temp->update(t);
	}

	for (unsigned int i = 0; i < arrows.size(); i++)
		this->arrows[i].update(t);
}

void ObjectHandler::addWall(vector pos, vector size, float angle)
{
	statObjects.push_back(Wall(pos, size, angle));
}

void ObjectHandler::addFan(vector pos, vector size, float angle, float velocity)
{
	fans.push_back(Fan(pos, size, angle, velocity));
}

void ObjectHandler::shootArrow(float angle, vector spd)
{
	//dynObjects.push_back(Arrow(vector(10, SCREEN_HEIGHT / 2), vector(20, 2), angle, spd));
	if(arrows.size() > 0)
		arrows.pop_back();
	arrows.push_back(Arrow(vector(10, SCREEN_HEIGHT/2), vector(20,2), angle, spd));

}