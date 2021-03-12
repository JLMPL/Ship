#pragma once
#include "Scene/SceneObject.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <vector>

class Explosion : public SceneObject
{
public:
	struct Particle
	{
		vec2 pos;
		vec2 dir;
	};

	Explosion(Scene* scene);
	~Explosion() = default;

	void ready(const vec2& origin, const sf::Color& color);
	void update(float dt) override final;
	void draw() override final;

private:
	std::vector<Particle> m_particles;
	std::vector<sf::Vertex> m_vertices;
	sf::Color m_color;
};