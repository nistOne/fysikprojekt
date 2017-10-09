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
	void shootArrow(float angle, float spd);

private:
	std::vector<Obj> statObjects;
	std::vector<Arrow> dynObjects;

	std::vector<Fan> fans;

	std::vector<Obj> objects;
};
