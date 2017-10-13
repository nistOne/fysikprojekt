#pragma once
#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH 800 
#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH_MIDDLE SCREEN_WIDTH/2 
#define SCREEN_HEIGHT_MIDDLE SCREEN_HEIGHT/2 


#define PAJ 3.141592f
#define SPEED 10.f

#define DEBUG true

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
	
	/*
	*	Structs and functions used to detect collision.
	*/

	struct Plane
	{
		vector normal;	// Ortogonal to plane.
		float length;	// Length from origo.
	};

	struct PlaneBox
	{
		Plane planes[4];
	};

	static PlaneBox planeBoxFromBoundingBox(boundingBox bbox)
	{
		// Create all four planes closing the bounding box.
		Plane planes[4];

		// Calc plane a (passes through point 1 and 2  in bbox).
		planes[0].normal = (bbox.pos3 - bbox.pos1).normalize();
		planes[0].length = dotP(bbox.pos1, planes[0].normal);

		// Calc plane b (passes through point 1 and 3 in bbox).
		planes[1].normal = (bbox.pos4 - bbox.pos3).normalize();
		planes[1].length = dotP(bbox.pos3, planes[1].normal);

		// Calc plane c (passes through point 2 and 4 in bbox).
		planes[2].normal = (bbox.pos1 - bbox.pos2).normalize();
		planes[2].length = dotP(bbox.pos2, planes[2].normal);

		// Calc plane d (passes through point 3 and 4 in bbox).
		planes[3].normal = (bbox.pos2 - bbox.pos4).normalize();
		planes[3].length = dotP(bbox.pos4, planes[3].normal);

		return PlaneBox{ planes[0], planes[1], planes[2], planes[3] };
	}

	static bool pointInFrontOfPlane(vector point, Plane plane)
	{
		return dotP(point, plane.normal) > plane.length;
	}

	static bool pointInsidePlaneBox(vector point, PlaneBox box)
	{
		/*
		* If one of the arrow's bbox corners is in front of all
		* the planes at once, then it's a hit.
		*/

		if (!bm::pointInFrontOfPlane(point, box.planes[0]))
			return false;
		if (!bm::pointInFrontOfPlane(point, box.planes[1]))
			return false;
		if (!bm::pointInFrontOfPlane(point, box.planes[2]))
			return false;
		if (!bm::pointInFrontOfPlane(point, box.planes[3]))
			return false;

		return true;
	}
}