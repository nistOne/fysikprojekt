#include "Fan.h"
#include "Window.h"

Fan::Fan(vector pos, vector size, float angle, float velocity) : Obj(pos, size, angle)
{
	this->velocity = velocity;

	vector vec_up(0.f, -1.f);
	vector vec_right(1.f, 0.f);

	if (this->angle != 0)
	{
		vec_up.rotate(this->angle);
		vec_right.rotate(this->angle);
	}

	this->windDirection = vec_up;

	area.pos3 = this->pos - vec_right * this->size.x / 2 + vec_up * this->size.y / 2;
	area.pos4 = this->pos + vec_right * this->size.x / 2 + vec_up * this->size.y / 2;
	
	area.pos1 = area.pos3 + vec_up * 5000;
	area.pos2 = area.pos4 + vec_up * 5000;

	// Setup particle system
	//this->pSystem.setEmitter(this->pos.asVector2f());
	//this->pSystem.setFanUpVector(vec_up.asVector2f());
	//this->pSystem.setFanRightVector(vec_right.asVector2f());
	//this->pSystem.setFanVelocity(this->velocity);
	//this->pSystem.setFanWidth(this->size.x);

	this->pSystem.setFanData(
		this->pos.asVector2f(),
		vec_up.asVector2f(),
		vec_right.asVector2f(),
		this->velocity,
		this->size.x
	);
}

Fan::~Fan()
{

}

void Fan::drawArea()
{
	sf::VertexArray quad(sf::Quads, 4);

	// Quads vertices are positioned clockwise.
	quad[0].position = area.pos1.asVector2f();
	quad[1].position = area.pos2.asVector2f();
	quad[2].position = area.pos4.asVector2f();
	quad[3].position = area.pos3.asVector2f();

	quad[0].color = sf::Color::Red;
	quad[1].color = sf::Color::Green;
	quad[2].color = sf::Color::Blue;
	quad[3].color = sf::Color::White;

	gWindow->draw(quad);
}

bm::boundingBox Fan::getArea()
{
	return this->area;
}

float Fan::getWindVelocity_asFloat()
{
	return this->velocity;
}

vector Fan::getWindDirection()
{
	return this->windDirection;
}

vector Fan::getWindVelocity_asVector()
{
	return this->windDirection * this->velocity;
}

void Fan::draw()
{
	if (DEBUG)
		drawArea();

	if(SHOWWIND)
		gWindow->draw(this->pSystem);

	Obj::draw();
}

void Fan::update(float t)
{
	this->pSystem.update(t);
}