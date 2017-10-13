#include "Arrow.h"
#include <stdio.h>

Arrow::Arrow(vector pos, vector size, float angle, vector spd) : Obj(pos, size, angle)
{

	this->dir = vector(cos(angle), sin(angle));
	this->pos = pos;
	this->speed = spd;
	this->A = PAJ * 0.395 * 0.395; //0.395 radie på pilen
	this->inAir = true;
	this->Fg = vector(0, GRAVITY * this->weight);
	this->Fd = vector(0, 0);
	this->Ff = vector(0, 0);
}

Arrow::~Arrow()
{
}

float Arrow::getAngle()
{
	vector temp = this->speed - (this->Ff / this->weight);

	return atanf(temp.y / temp.x) * 180 / PAJ; 
}

void Arrow::update(float t, vector spdWnd)
{
	if (inAir)
	{
		//Update arrow position
		this->pos = this->pos + (this->speed * t);

		//Update arrow speed
		this->speed = this->speed + this->acc * t;

		//Update arrow direction
		this->dir = this->speed.normalize();

		//Update arrow acceleration
		this->acc = ((this->Fd + this->Ff + this->Fg) / this->weight);

		//Update arrow forces
		this->Fd = (this->spdRelWind * this->spdRelWind * this->Cd) * (this->dir * (-1));
		this->Ff = spdWnd * this->weight;

		//Update spdRelWind
		this->spdRelWind = this->speed - spdWnd;

		//Set arrow position and rotate the texture
		this->shape.setRotation(getAngle());
		this->shape.setPosition(sf::Vector2f(pos.x, pos.y));

		/*
		*	Update bounding box
		*/

		vector vec_up(0.f, -1.f);
		vector vec_right(1.f, 0.f);

		vec_up.rotate(getAngle());
		vec_right.rotate(getAngle());

		bbox.pos1 = this->pos - vec_right * this->size.x / 2 + vec_up * this->size.y / 2;
		bbox.pos2 = this->pos + vec_right * this->size.x / 2 + vec_up * this->size.y / 2;
		bbox.pos3 = this->pos - vec_right * this->size.x / 2 - vec_up * this->size.y / 2;
		bbox.pos4 = this->pos + vec_right * this->size.x / 2 - vec_up * this->size.y / 2;
	}
}

bool Arrow::collideWith(bm::boundingBox box)
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

bool Arrow::isFlying()
{
	return this->inAir;
}

void Arrow::endFlight()
{
	this->inAir = false;
}

void Arrow::reset()
{
	this->inAir = true;
}

void Arrow::addForceToArrow(vector force)
{

}