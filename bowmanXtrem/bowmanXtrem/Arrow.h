#pragma once
#include "Object.h"
#include <math.h>

#define GRAVITY 9.82f
#define AIRDENSITY 1.225f

class Arrow : public Obj
{
public:

	Arrow(vector pos, vector size, float angle, vector spd);
	~Arrow();
		
	vector getUp()	{ return vector(-dir.y, dir.x); }
	float getAngle() {return atanf((dir.y / dir.x)) * 180 / PAJ;}

	void update(float t) override;

	virtual void draw_debug() { Obj::draw(); }

	bool isFlying();
	void endFlight();
	void reset();

private:
	vector dir;
	vector speed;
	vector acc;
	vector xAxis = (1.0f, 0.0f);
	float A;
	float Cd;

	bool inAir;
};

