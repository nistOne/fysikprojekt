#include "ObjectHandler.h"
#include "Wall.h"

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

void ObjectHandler::update()
{
}

void ObjectHandler::addWall(vector pos, vector size, float angle)
{
	statObjects.push_back(Wall(pos, size, angle));
}
