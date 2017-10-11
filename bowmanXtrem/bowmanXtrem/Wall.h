#pragma once
#include "Object.h"

class Wall : public Obj
{
public:
	Wall(vector pos, vector size, float angle);
	~Wall();

	virtual void draw_debug() {}

private:

	sf::Color color;

};