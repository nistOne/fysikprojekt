#include "Arrow.h"
#include <stdio.h>

Arrow::Arrow(vector pos, vector size, float angle, vector spd) : Obj(pos, size, angle)
{

	this->dir = vector(cos(angle), sin(angle));
	this->pos = pos;
	this->speed = spd;
	this->acc.x = 0.0;
	this->acc.y = GRAVITY;
	this->A = PAJ * 0.395 * 0.395; //0.395 radie på pilen
}

Arrow::~Arrow()
{
}

void Arrow::update(float t)
{

	//Update arrow position
	this->pos.x = this->pos.x + this->speed.x * t;
	this->pos.y = this->pos.y + this->speed.y * t;

	//Update arrow speed
	this->speed.x = this->speed.x + this->acc.x * t;
	this->speed.y = this->speed.y + this->acc.y * t;

	//Update arrow direction
	this->dir = this->speed.normalize();

	//Update arrow acceleration
	this->acc.x = this->acc.x + (-1.5) * t;

	//Set arrow position and rotate the texture
	this->shape.setRotation(getAngle());
	this->shape.setPosition(sf::Vector2f(pos.x, pos.y));


	/*
	vector pre = pos;

	float a = 0.000001;

	vector res;
	res.x = dir.x * spd;
	res.y = dir.y * spd;

	pos = pos + res;

	pos.y = SCREEN_HEIGHT_MIDDLE + res.y*t + ((a*t*t) / 2);

	this->shape.setRotation(getAngle());
	this->shape.setPosition(sf::Vector2f(pos.x, pos.y));
	*/
}

bool Arrow::collideWith(bm::bbox box)
{
	/*
	*	NOTE:	This function uses the term "plane" to describe
	*			the lines through the bbox sides.
	*/

	bool insideBox;

	// Normals to all planes, each pointing at the center of bbox.
	vector a_normal;
	vector b_normal;
	vector c_normal;
	vector d_normal;

	// Lenght to each plane from origo.
	float a_length;
	float b_length;
	float c_length;
	float d_length;

	// Calc plane a (passes through point 1 and 2  in bbox).
	a_normal = (box.pos3 - box.pos1).normalize();
	a_length = bm::dotP(box.pos1, a_normal);

	// Calc plane b (passes through point 1 and 3 in bbox).
	b_normal = (box.pos4 - box.pos3).normalize();
	b_length = bm::dotP(box.pos3, b_normal);

	// Calc plane c (passes through point 2 and 4 in bbox).
	c_normal = (box.pos1 - box.pos2).normalize();
	c_length = bm::dotP(box.pos2, c_normal);

	// Calc plane d (passes through point 3 and 4 in bbox).
	d_normal = (box.pos2 - box.pos4).normalize();
	d_length = bm::dotP(box.pos4, d_normal);

	/*
	* If one of the arrow's bbox corners is in front of all
	* the planes at once, then it's a hit.
	*
	* When starting to check each point, assume collision
	* and prove false if not.
	*/

	// Check point 1:
	insideBox = true;
	if (!bm::pointInFrontOfPlane(this->bbox.pos1, a_normal, a_length))
		insideBox = false;
	else if (!bm::pointInFrontOfPlane(this->bbox.pos1, b_normal, b_length) && insideBox)
		insideBox = false;
	else if (!bm::pointInFrontOfPlane(this->bbox.pos1, c_normal, c_length) && insideBox)
		insideBox = false;
	else if (!bm::pointInFrontOfPlane(this->bbox.pos1, d_normal, d_length) && insideBox)
		insideBox = false;

	// If inside, return early.
	if (insideBox)
		return insideBox;
	
	// Check point 2
	insideBox = true;
	if (!bm::pointInFrontOfPlane(this->bbox.pos2, a_normal, a_length))
		insideBox = false;
	else if (!bm::pointInFrontOfPlane(this->bbox.pos2, b_normal, b_length) && insideBox)
		insideBox = false;
	else if (!bm::pointInFrontOfPlane(this->bbox.pos2, c_normal, c_length) && insideBox)
		insideBox = false;
	else if (!bm::pointInFrontOfPlane(this->bbox.pos2, d_normal, d_length) && insideBox)
		insideBox = false;

	// If inside, return early.
	if (insideBox)
		return insideBox;

	// Check point 3
	insideBox = true;
	if (!bm::pointInFrontOfPlane(this->bbox.pos3, a_normal, a_length))
		insideBox = false;
	else if (!bm::pointInFrontOfPlane(this->bbox.pos3, b_normal, b_length) && insideBox)
		insideBox = false;
	else if (!bm::pointInFrontOfPlane(this->bbox.pos3, c_normal, c_length) && insideBox)
		insideBox = false;
	else if (!bm::pointInFrontOfPlane(this->bbox.pos3, d_normal, d_length) && insideBox)
		insideBox = false;
	
	// If inside, return early.
	if (insideBox)
		return insideBox;

	// Check point 4
	insideBox = true;
	if (!bm::pointInFrontOfPlane(this->bbox.pos4, a_normal, a_length))
		insideBox = false;
	else if (!bm::pointInFrontOfPlane(this->bbox.pos4, b_normal, b_length) && insideBox)
		insideBox = false;
	else if (!bm::pointInFrontOfPlane(this->bbox.pos4, c_normal, c_length) && insideBox)
		insideBox = false;
	else if (!bm::pointInFrontOfPlane(this->bbox.pos4, d_normal, d_length) && insideBox)
		insideBox = false;

	return insideBox;
}