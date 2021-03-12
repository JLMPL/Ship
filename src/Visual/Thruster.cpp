#include "Thruster.hpp"
#include "Renderer.hpp"
#include "Core/Timer.hpp"

Thruster::Thruster()
{
	m_verts[0] = sf::Vertex(vec2(m_width, 0), sf::Color::Blue);
	m_verts[1] = sf::Vertex(vec2(-m_width, 0), sf::Color::Blue);
	m_verts[2] = sf::Vertex(vec2(-m_width * 0.7, m_length), sf::Color::Transparent);
	m_verts[3] = sf::Vertex(vec2(m_width * 0.7, m_length), sf::Color::Transparent);
}

void Thruster::update()
{
	m_timer += timer::delta * 50.f;

	m_verts[2].position.y = m_length + sin(m_timer);
	m_verts[3].position.y = m_length + cos(m_timer);
}

void Thruster::draw()
{
	if (m_visible)
		Renderer.drawScaled(m_verts.data(), m_verts.size(), sf::TriangleFan, m_tr);
}

void Thruster::setTransform(const vec2& pos, float angle, float offset)
{
	m_tr = sf::Transform();
	m_tr.translate(pos).rotate(angle * (180.f / M_PI)).translate(vec2(0, offset));
}

void Thruster::setVisible(bool visible)
{
	m_visible = visible;
}

void Thruster::setLength(float length)
{
	m_length = length;
}