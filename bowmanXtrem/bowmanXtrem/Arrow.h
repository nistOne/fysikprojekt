#pragma once
#include "Globals.h"
#include "Object.h"

class Arrow : public Obj
{
public:
	Arrow(vector pos, vector size, float angle, float spd);
	~Arrow();
		
	vector getUp()	{ return vector(-dir.y, dir.x); }
	float getAngle()	{return atan((dir.y / dir.x)) * 180 / 3.14;}

	void update() override;

private:
	vector dir;
	float spd;
};

