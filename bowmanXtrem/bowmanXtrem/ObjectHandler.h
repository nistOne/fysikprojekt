#pragma once
#include <Vector>
#include "Object.h"
#include "Arrow.h"

class ObjectHandler
{
public:
	ObjectHandler();
	~ObjectHandler();

	void draw();
	void update(int t);
	void addWall(vector pos, vector size, float angle);
	void shootArrow(float angle, float spd);

private:
	std::vector<Obj> statObjects;
	std::vector<Arrow> dynObjects;
};
