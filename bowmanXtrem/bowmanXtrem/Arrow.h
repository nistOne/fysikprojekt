#pragma once
#include "Object.h"
#include <math.h>
#include "Window.h"

#define GRAVITY 9.82f
#define AIRDENSITY 1.225f

class Arrow : public Obj
{
public:

	Arrow(vector pos, vector size, float angle, vector spd);
	~Arrow();
		
	vector getUp()	{ return vector(-dir.y, dir.x); }
	float getAngle(); 

	void update(float t, vector spdWnd); // override;

	virtual void draw_debug() { Obj::draw(); }

	bool isFlying();
	void endFlight();
	void reset();
	void addForceToArrow(vector force);
	vector getSpeed();

private:
	sf::Texture tex;
	vector dir;
	vector speed;
	vector acc;
	vector xAxis = (1.0f, 0.0f);
	vector Fd;
	vector Ff;
	vector Fg;
	vector spdRelWind;

	sf::Font font;
	sf::Text arrText;
	

	float A;
	float Cd = 0.0001;
	float weight = 0.400;
	float length = 0.8;

	bool inAir;
};

