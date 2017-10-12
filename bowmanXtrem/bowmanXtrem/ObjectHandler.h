#pragma once
#include <Vector>
#include "Object.h"
#include "Arrow.h"
#include "Fan.h"

class ObjectHandler
{
public:

	ObjectHandler();
	~ObjectHandler();

	void draw();
	void update(float t);
	void addWall(vector pos, vector size, float angle);
	void addFan(vector pos, vector size, float angle, float velocity);
	void shootArrow(float angle, vector spd);
	void reset();

private:
	std::vector<Obj> walls;
	std::vector<Arrow> arrows;
	std::vector<Fan> fans;
};
