#pragma once
#include "Object.h"

#define GRAVITY 9.82
#define AIRDENSITY 1.225

class Arrow : public Obj
{
public:

	Arrow(vector pos, vector size, float angle, vector spd);
	~Arrow();
		
	vector getUp()	{ return vector(-dir.y, dir.x); }
	float getAngle()	{return atan((dir.y / dir.x)) * 180 / PAJ;}
	void update(float t);


private:
	vector dir;
	vector speed;
	vector acc;
	vector xAxis = (1.0f, 0.0f);
	float A;
	float Cd;

	bool collideWith(bm::bbox box);
};

