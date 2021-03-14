#include "Pulse.hpp"
#include "Renderer.hpp"

Pulse::Pulse(Scene* scene)
 : SceneObject(scene)
{
    m_name = "pulse";

    m_circle.setFillColor(sf::Color::Transparent);
    m_circle.setOutlineThickness(0.1);
}

void Pulse::ready(const vec2& pos)
{
    m_pos = pos;
    m_radius = 0.f;
}

void Pulse::update(float dt)
{
    m_radius += dt * 5.f;
    m_color.a = std::max(0.f, m_color.a - dt * 150.f);

    if (m_color.a == 0)
        destroy();

    m_circle.setOrigin({m_radius, m_radius});
    m_circle.setOutlineColor(m_color);
    m_circle.setRadius(m_radius);
    m_circle.setPosition(m_pos);
}

void Pulse::draw()
{
    Renderer.drawScaled(m_circle);
}