#include "ObjectHandler.h"
#include "Wall.h"
#include "Arrow.h"
#include "Fan.h"

ObjectHandler::ObjectHandler()
{
	aimLine.push_back(Wall(
		vector(SCREEN_WIDTH_MIDDLE, SCREEN_HEIGHT_MIDDLE), 
		vector(200, 10), 
		0.0f));
}

ObjectHandler::~ObjectHandler()
{
}

void ObjectHandler::draw(bool aim)
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

	if (true)
		aimLine.front().draw();
}

void ObjectHandler::update(float t)
{
	
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

void ObjectHandler::updateAimLine(vector start, vector vec)
{
	aimLine.front().editLine(start, vec);

	//statObjects.front().editLine(start, vec);
}
