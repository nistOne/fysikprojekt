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
	int update(float t);
	void addWall(vector pos, vector size, float angle);
	void addTarget(vector pos, vector size, float angle);
	void addFan(vector pos, vector size, float angle, float velocity);
	void shootArrow(float angle, vector spd);
	void updateAimLine(vector start, vector vec);
	void reset();
	void clear();

	bool collisionArrow_BoundingBox(Arrow arrow, bm::boundingBox bbox);
	vector collisionArrow_Fan(Arrow arrow, Fan fan);

private:
	std::vector<Wall> walls;
	std::vector<Wall> target;
	std::vector<Arrow> arrows;
	std::vector<Fan> fans;


	/*
	*	Structs and functions used to detect collision.
	*/

	struct Plane
	{
		vector normal;	// Ortogonal to plane.
		float length;	// Length from origo.
	};
	std::vector<Wall> aimLine;
};
