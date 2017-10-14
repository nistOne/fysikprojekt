#pragma once
#include <SFML/Graphics.hpp>

#define uint unsigned int

class windParticleSystem : public sf::Drawable, public sf::Transformable
{
public:

	windParticleSystem();
	~windParticleSystem();

	void setParticleCount(uint count);
	void setFanUpVector(sf::Vector2f vec);
	void setFanRightVector(sf::Vector2f vec);
	void setFanVelocity(float velocity);
	void setFanWidth(float width);

	void setFanData(
		sf::Vector2f vec_pos,
		sf::Vector2f vec_up,
		sf::Vector2f vec_right,
		float velocity,
		float width);

	void setEmitter(sf::Vector2f position);
	void update(float t);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2f scale(sf::Vector2f vec, float scalar);

	struct Particle
	{
		sf::Vector2f velocity;
		float lifetime;
	};

	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	sf::Vector2f m_emitter;

	// Fan specific variables
	sf::Vector2f fan_up;
	sf::Vector2f fan_right;
	float fan_velocity;
	float fan_width;

	void resetParticle(std::size_t index);
};