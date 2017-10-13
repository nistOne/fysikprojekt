#pragma once
#include "Object.h"
#include <math.h>

#define GRAVITY 9.82
#define AIRDENSITY 1.225

class Arrow : public Obj
{
public:

	Arrow(vector pos, vector size, float angle, vector spd);
	~Arrow();
		
	vector getUp()	{ return vector(-dir.y, dir.x); }
	float getAngle(); 

	void update(float t, vector spdWnd); // override;
	bool collideWith(bm::boundingBox box);
	bool isFlying();
	void endFlight();
	void reset();
	void addForceToArrow(vector force);

	virtual void draw_debug() { Obj::draw(); }

private:
	vector dir;
	vector speed;
	vector acc;
	vector xAxis = (1.0f, 0.0f);
	vector Fd;
	vector Ff;
	vector Fg;
	vector spdRelWind;

	float A;
	float Cd = 0.0001;
	float weight = 0.400;
	float length = 0.8;

	bool inAir;
};

