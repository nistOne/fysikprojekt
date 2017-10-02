#pragma once
#include <Vector>
#include "Object.h"

class ObjectHandler
{
public:
	ObjectHandler();
	~ObjectHandler();

	void draw();
	void update();
	void addWall(vector pos, vector size, float angle);

private:
	std::vector<Obj> statObjects;
	std::vector<Obj> dynObjects;
};
