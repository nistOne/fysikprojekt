#pragma once
#include "Object.h"
#include "Wind_particleSystem.h"

class Fan : public Obj
{
private:

	bm::boundingBox area;
	float velocity;
	vector windDirection;

	windParticleSystem pSystem;

public:

	Fan(vector pos, vector size, float angle, float velocity);
	~Fan();

	void drawArea();

	bm::boundingBox getArea();
	float getWindVelocity_asFloat();
	vector getWindDirection();
	vector getWindVelocity_asVector();

	virtual void draw();
	virtual void update(float t);
};