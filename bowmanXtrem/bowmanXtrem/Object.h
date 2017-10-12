#pragma once
#include "Globals.h"

class Obj
{
public:

	Obj(vector pos, vector size, float angle);
	~Obj();

	virtual void draw();
	virtual void update(float t);
	bm::boundingBox getBoundingBox();

protected:

	sf::RectangleShape shape;

	vector pos;
	vector size;
	float angle;
	bm::boundingBox bbox;
};

