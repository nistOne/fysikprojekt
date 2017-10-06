#pragma once
#include "Globals.h"

class Obj
{
public:

	Obj(vector pos, vector size, float angle);
	~Obj();

	virtual void draw();
	virtual void update();
	void setRenderTarget(sf::RenderTarget * window);

protected:

	sf::RenderTarget * window;

	sf::RectangleShape shape;

	vector pos;
	vector size;
	float angle;
	bm::bbox bbox;
};

