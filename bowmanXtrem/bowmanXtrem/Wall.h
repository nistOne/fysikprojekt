#pragma once
#include "Object.h"

class Wall : public Obj
{
public:
	Wall(vector pos, vector size, float angle);
	~Wall();

private:

	sf::Color color;

};