#pragma once
#include "Globals.h"

class Obj
{
public:

	Obj(vector pos, vector size, float angle);
	~Obj();

	virtual void draw();
	virtual void update(float t);

	virtual void draw_debug() {}

protected:

	//sf::RenderTarget * window;

	sf::RectangleShape shape;

	vector pos;
	vector size;
	float angle;
	bm::boundingBox bbox;
};

