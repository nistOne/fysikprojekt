#pragma once
#include "Object.h"
#include <math.h>

class Arrow : public Obj
{
public:

	Arrow(vector pos, vector size, float angle, float spd);
	~Arrow();
		
	vector getUp()	{ return vector(-dir.y, dir.x); }
	float getAngle()	{return atanf((dir.y / dir.x)) * 180 / PAJ;}

	void update(float t) override;
	bool collideWith(bm::boundingBox box);

	virtual void draw_debug() {}

private:
	vector dir;
	float spd;

};

