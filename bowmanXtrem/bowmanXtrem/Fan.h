#pragma once
#include "Object.h"

#include <iostream>

class Fan : public Obj
{
private:

	bm::boundingBox area;
	float velocity;

public:

	Fan(vector pos, vector size, float angle, float velocity);
	~Fan();

	void drawArea();

	virtual void draw_debug() { drawArea(); }
};