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

	area.pos3 = this->pos - vec_right * this->size.x / 2 + vec_up * this->size.y / 2;
	area.pos4 = this->pos + vec_right * this->size.x / 2 + vec_up * this->size.y / 2;
	
	area.pos1 = area.pos3 + vec_up * 5000;
	area.pos2 = area.pos4 + vec_up * 5000;
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

void Fan::draw()
{
	if (DEBUG)
		drawArea();


	Obj::draw();
}