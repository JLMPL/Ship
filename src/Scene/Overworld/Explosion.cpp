#include "Explosion.hpp"
#include "Scene/Scene.hpp"
#include "Random.hpp"
#include "Renderer.hpp"

Explosion::Explosion(Scene* scene)
	: SceneObject(scene)
{
	m_name = "explosion";
	m_particles.resize(10);
	m_vertices.resize(m_particles.size() * 2);
}

void Explosion::ready(const vec2& origin, const sf::Color& color)
{
	for (auto& particle : m_particles)
	{
		particle.pos = origin;
		particle.dir = math::normalize(vec2(rng::inRange(-1.f, 1.f), rng::inRange(-1.f, 1.f)));
	}

	m_color = color;
}

void Explosion::update(float dt)
{
	for (auto& particle : m_particles)
	{
		particle.pos += particle.dir * dt * 15.f;
	}

	m_color.a = std::max(0, int(m_color.a - dt * 800.f));

	if (m_color.a == 0)
		destroy();
}

void Explosion::draw()
{
	int i = 0;
	for (auto& pt : m_particles)
	{
		m_vertices[i].position = pt.pos;
		m_vertices[i].color = m_color;

		m_vertices[i+1].position = pt.pos - pt.dir;
		m_vertices[i+1].color = sf::Color::Transparent;

		i += 2;
	}

	Renderer.drawScaled(m_vertices.data(), m_vertices.size(), sf::Lines);
}