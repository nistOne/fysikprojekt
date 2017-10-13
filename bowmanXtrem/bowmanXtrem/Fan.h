#pragma once
#include "Object.h"

#include <iostream>

class Fan : public Obj
{
private:

	bm::boundingBox area;
	float velocity;
	vector windDirection;

public:

	Fan(vector pos, vector size, float angle, float velocity);
	~Fan();

	void drawArea();

	bm::boundingBox getArea();
	float getWindVelocity_asFloat();
	vector getWindDirection();
	vector getWindVelocity_asVector();

	virtual void draw();
};