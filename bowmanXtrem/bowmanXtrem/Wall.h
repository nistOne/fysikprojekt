#pragma once
#include "Object.h"

class Wall : public Obj
{
public:
	Wall(vector pos, vector size, float angle);
	~Wall();

	virtual void draw_debug() {}
	void editLine(vector pos, vector line);

private:

	sf::Color color;

};