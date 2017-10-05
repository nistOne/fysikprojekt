#pragma once
#include "Object.h"

class Arrow : public Obj
{
public:

	Arrow(vector pos, vector size, float angle, float spd);
	~Arrow();
		
	vector getUp()	{ return vector(-dir.y, dir.x); }
	float getAngle()	{return atan((dir.y / dir.x)) * 180 / PAJ;}

	void update(int t);

private:
	vector dir;
	float spd;

	bool collideWith(bm::bbox box);
};

