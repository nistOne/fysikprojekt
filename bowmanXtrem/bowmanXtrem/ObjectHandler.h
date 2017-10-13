#pragma once
#include <Vector>
#include "Wall.h"
#include "Arrow.h"
#include "Fan.h"

class ObjectHandler
{
public:

	ObjectHandler();
	~ObjectHandler();

	void draw(bool aim);
	void update(float t);
	void addWall(vector pos, vector size, float angle);
	void addFan(vector pos, vector size, float angle, float velocity);
	void shootArrow(float angle, vector spd);
	void updateAimLine(vector start, vector vec);
	void reset();

private:
	std::vector<Wall> walls;
	//std::vector<Obj> walls;
	std::vector<Arrow> arrows;
	std::vector<Fan> fans;
	std::vector<Wall> aimLine;
};
