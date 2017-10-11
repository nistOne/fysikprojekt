#pragma once
#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH 800 
#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH_MIDDLE SCREEN_WIDTH/2 
#define SCREEN_HEIGHT_MIDDLE SCREEN_HEIGHT/2 

#define SPEED 0.02f
#define PAJ 3.141592f

#define DEBUG false

struct vector
{
	float x;
	float y;

	vector(float x = 0, float y = 0)
	{
		this->x = x;
		this->y = y;
	}

	vector operator+ (vector vec2) {
		vector temp;
		temp.x = this->x + vec2.x;
		temp.y = this->y + vec2.y;
		return temp;
	};

	vector operator- (vector vec2) {
		vector temp;
		temp.x = this->x - vec2.x;
		temp.y = this->y - vec2.y;
		return temp;
	};

	vector operator* (float scalar)
	{
		return vector(x*scalar, y*scalar);
	}

	vector operator/ (float denominate)
	{
		vector temp;
		temp.x = this->x / denominate;
		temp.y = this->y / denominate;
		return temp;
	}

	vector scale(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
	}

	vector normalize ()
	{
		float temp = sqrt(this->x*(this->x) + this->y*this->y);
		vector ret(this->x / temp, this->y / temp);
		return ret;
	}

	void rotate(float angle)
	{
		angle = angle * PAJ / 180;
		float tempX = x*cos(angle) - y*sin(angle);
		float tempY = x*sin(angle) + y*cos(angle);

		x = tempX;
		y = tempY;
	}

	float length()
	{
		return std::sqrt( (this->x * this->x) + (this->y * this->y) );
	}

	sf::Vector2f asVector2f()
	{
		return sf::Vector2f(x, y);
	}
};

namespace bm {

	struct boundingBox
	{
		vector pos1;
		vector pos2;
		vector pos3;
		vector pos4;
	};

	static float dotP(vector a, vector b)
	{
		return a.x * b.x + a.y * b.y;
	}
	
	// Projection of vector a on vector b
	static vector proj(vector a, vector b)
	{
		b.scale( dotP(a, b) / (std::pow(b.length(), 2)) );
		return b;
	}
	
	static bool pointInFrontOfPlane(vector point, vector plane_normal, float plane_length)
	{
		return dotP(point, plane_normal) > plane_length;
	}
}