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

	bool collisionArrow_BoundingBox(Arrow arrow, bm::boundingBox bbox);
	vector collisionArrow_Fan(Arrow arrow, Fan fan);

private:
	std::vector<Obj> walls;
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
};
