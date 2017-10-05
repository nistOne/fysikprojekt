#pragma once
#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH 800 
#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH_MIDDLE SCREEN_WIDTH/2 
#define SCREEN_HEIGHT_MIDDLE SCREEN_HEIGHT/2 

#define SPEED 0.02

#define PAJ 3.14

struct vector
{
	float x;
	float y;

	vector(float x = 0, float y = 0)
	{
		this->x = x;
		this->y = y;
	}

	vector add(vector vec2) {
		vector temp;
		temp.x = this->x + vec2.x;
		temp.y = this->y + vec2.y;
		return temp;
	};
};

struct bbox
{
	vector pos1;
	vector pos2;
	vector pos3;
	vector pos4;
};