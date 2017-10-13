#include "Wind_particleSystem.h"
#include "Globals.h"

windParticleSystem::windParticleSystem()
{

}

windParticleSystem::~windParticleSystem()
{

}

void windParticleSystem::setParticleCount(uint count)
{
	m_particles = std::vector<Particle>(count);
}

void windParticleSystem::setFanUpVector(sf::Vector2f vec)
{
	fan_up = vec;
}

void windParticleSystem::setFanRightVector(sf::Vector2f vec)
{
	fan_right = vec;
}

void windParticleSystem::setFanVelocity(float velocity)
{
	fan_velocity = velocity;
	setParticleCount(velocity * 20);
}

void windParticleSystem::setFanWidth(float width)
{
	fan_width = width;
}

void windParticleSystem::setFanData(
	sf::Vector2f vec_pos,
	sf::Vector2f vec_up,
	sf::Vector2f vec_right,
	float velocity,
	float width)
{
	int particleCount;

	fan_up = vec_up;
	fan_right = vec_right;
	fan_velocity = velocity;
	fan_width = width;

	particleCount = velocity * width;

	m_particles = std::vector<Particle>(particleCount);
	m_vertices = sf::VertexArray(sf::Points, particleCount);
	m_emitter = vec_pos;

	int limit;
	if (particleCount > 100)
		limit = sqrt(particleCount);
	else if (particleCount > 50)
		limit = particleCount;
	else
		limit = particleCount * 2;

	for (unsigned int i = 0; i < limit; i++)
	{
		update(1.5f);
	}
}

void windParticleSystem::setEmitter(sf::Vector2f position)
{
	m_emitter = position;
}

void windParticleSystem::update(float t)
{
	for (std::size_t i = 0; i < m_particles.size(); ++i)
	{
		// update the particle lifetime
		Particle& p = m_particles[i];
		p.lifetime -= t;

		// if the particle is dead, respawn it
		if (p.lifetime <= 0)
			resetParticle(i);

		// update the position of the corresponding vertex
		m_vertices[i].position += p.velocity * t;

		// update the alpha (transparency) of the particle according to its lifetime
		float ratio = p.lifetime / t;
		m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
	}
}

void windParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// our particles don't use a texture
	states.texture = NULL;

	// draw the vertex array
	target.draw(m_vertices, states);
}

sf::Vector2f windParticleSystem::scale(sf::Vector2f vec, float scalar)
{
	return sf::Vector2f(vec.x * scalar, vec.y * scalar);
}

void windParticleSystem::resetParticle(std::size_t index)
{
	// give a random velocity and lifetime to the particle
	float speed = std::rand() % (int)fan_velocity*3 + fan_velocity*10;
	m_particles[index].velocity = fan_up * speed;
	m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 5000).asSeconds();

	float offset = std::rand() % (int)fan_width - (fan_width / 2.f);

	// reset the position of the corresponding vertex
	m_vertices[index].position = m_emitter + scale(fan_right, offset);
}