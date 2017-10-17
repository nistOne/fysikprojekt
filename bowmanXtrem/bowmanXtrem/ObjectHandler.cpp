#include "ObjectHandler.h"
#include "Wall.h"
#include "Arrow.h"
#include "Fan.h"

#include <iostream>

//#include <iostream>

ObjectHandler::ObjectHandler()
{
	aimLine.push_back(Wall(
		vector(0,0), 
		vector(0, 10), 
		0.0f));
}

ObjectHandler::~ObjectHandler()
{
}

void ObjectHandler::draw(bool aim)
{
	for (unsigned int i = 0; i < walls.size(); i++)
	{
		walls[i].draw();
	}

	for (unsigned int i = 0; i < fans.size(); i++)
	{
		fans[i].draw();
	}

	for (unsigned int i = 0; i < arrows.size(); i++)
	{
		arrows[i].draw();
	}

	if (aim)
		aimLine.front().draw();

	target.front().draw();
}

int ObjectHandler::update(float t)
{
	int returnValue = 0; 

	for (unsigned int i = 0; i < arrows.size(); i++)
	{
		for (unsigned int j = 0; j < walls.size() && this->arrows[i].isFlying(); j++)
		{
			//if (this->arrows[i].collideWith(walls[j].getBoundingBox()))
			if(collisionArrow_BoundingBox(this->arrows[i], walls[j].getBoundingBox()))
			{
				this->arrows[i].endFlight();
			}
		}

		if (collisionArrow_BoundingBox(this->arrows[i], this->target.front().getBoundingBox()))
		{
			this->arrows[i].endFlight();
			std::cout << "TARGET DOWN!!!!!!!!" << std::endl;
			returnValue = 1;
		}

		//for (unsigned int j = 0; j < fans.size(); j++)
		//{
		//	vector temp = collisionArrow_Fan(this->arrows[i], fans[j]);
		//	if (temp != vector(0.f, 0.f))
		//	{
		//		std::cout << "COLLISION DETECTED!" << std::endl;
		//	}
		//	else
		//		std::cout << "Lame.." << std::endl;
		//}

		vector fanSum;	
		for (int i = 0; i < this->fans.size(); i++)
		{
			fanSum = fanSum + this->collisionArrow_Fan(arrows.front(), fans.at(i));
		}

		this->arrows[i].update(t, fanSum);
	}

	
	


	if (SHOWWIND)
	{
		for (unsigned int i = 0; i < fans.size(); i++)
		{
			this->fans[i].update(t);
		}
	}

	return returnValue;
}

void ObjectHandler::addWall(vector pos, vector size, float angle)
{
	walls.push_back(Wall(pos, size, angle));
}

void ObjectHandler::addTarget(vector pos, vector size, float angle)
{
	target.push_back(Wall(pos, size, angle));
	target.front().setColor(sf::Color::Magenta);
}

void ObjectHandler::addFan(vector pos, vector size, float angle, float velocity)
{
	fans.push_back(Fan(pos, size, angle, velocity));
}

void ObjectHandler::shootArrow(float angle, vector spd)
{
	while (arrows.size() > 0)
	{
		arrows.pop_back();
	}
	arrows.push_back(Arrow(vector(10, SCREEN_HEIGHT/2), vector(20,2), angle, spd / SCALE));
}

void ObjectHandler::updateAimLine(vector start, vector vec)
{
	aimLine.front().editLine(start, vec);

	//statObjects.front().editLine(start, vec);
}
void ObjectHandler::reset()
{
	for (unsigned int i = 0; i < this->arrows.size(); i++)
	{
		this->arrows[i].reset();
	}
}

void ObjectHandler::clear()
{

	this->walls.clear();
	this->target.clear(); 
	this->arrows.clear();
	this->fans.clear();
}

bool ObjectHandler::collisionArrow_BoundingBox(Arrow arrow, bm::boundingBox bbox)
{
	/*
	*	NOTE:	This function uses the term "plane" to describe
	*			the lines through the bbox sides.
	*/

	bool insideBox;

	bm::boundingBox arrowBox = arrow.getBoundingBox();
	bm::PlaneBox planeBox = bm::planeBoxFromBoundingBox(bbox);

	/*
	* When starting to check each point, assume collision
	* and prove false if not.
	*/

	// ------ Check point 1 ------ //
	insideBox = true;
	if (!bm::pointInsidePlaneBox(arrowBox.pos1, planeBox))
		insideBox = false;

	// If inside, return early.
	if (insideBox)
		return insideBox;

	// ------ Check point 2 ------ //
	insideBox = true;
	if (!bm::pointInsidePlaneBox(arrowBox.pos2, planeBox))
		insideBox = false;

	// If inside, return early.
	if (insideBox)
		return insideBox;

	// ------ Check point 3 ------ //
	insideBox = true;
	if (!bm::pointInsidePlaneBox(arrowBox.pos3, planeBox))
		insideBox = false;

	// If inside, return early.
	if (insideBox)
		return insideBox;

	// ------ Check point 4 ------ //
	insideBox = true;
	if (!bm::pointInsidePlaneBox(arrowBox.pos4, planeBox))
		insideBox = false;

	return insideBox;
}

vector ObjectHandler::collisionArrow_Fan(Arrow arrow, Fan fan)
{
	/*
	*	This function checks if the arrows bum
	*	is inside a fans' area of wind. If true,
	*	retun the fans' wind-velocity-vector.
	*/

	vector arrowBum;
	bm::PlaneBox fan_planeBox;
	bm::boundingBox arrow_bBox;
	
	arrow_bBox = arrow.getBoundingBox();
	arrowBum = arrow_bBox.pos3 + (arrow_bBox.pos1 - arrow_bBox.pos3) * 0.5f;
	fan_planeBox = bm::planeBoxFromBoundingBox(fan.getArea());

	// Check if arrow is not affected by fan.
	if (!bm::pointInsidePlaneBox(arrowBum, fan_planeBox))
		return vector(0.f, 0.f);

	// .. else return fans wind-velocity-vector.
	return fan.getWindVelocity_asVector();
}

vector ObjectHandler::getArrowSpeed()
{
	return this->arrows.front().getSpeed();
}