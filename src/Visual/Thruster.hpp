#pragma once
#include "Core/Math.hpp"
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <array>

class Thruster
{
public:
	Thruster();
	~Thruster() = default;

	void update();
	void draw();

	void setTransform(const vec2& pos, float angle, float offset);
	void setVisible(bool visible);

	void setLength(float length);

private:
	std::array<sf::Vertex, 4> m_verts;
	sf::Transform m_tr;

	float m_width = 0.5;
	float m_length = 3.f;

	float m_timer = 0.f;
	bool m_visible = false;
};