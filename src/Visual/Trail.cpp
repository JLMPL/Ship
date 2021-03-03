#include "Trail.hpp"
#include "Core/Timer.hpp"
#include "Renderer.hpp"

void Trail::update()
{
    m_timer += sf::seconds(timer::delta);

    if (m_timer > sf::seconds(m_interval))
    {
        m_verts.push_back(sf::Vertex(m_pos, m_color));
        m_timer = sf::seconds(0);
    }

    if (m_verts.size() > 100)
        m_verts.erase(m_verts.begin());

    for (int i = 0; i < m_verts.size(); i++)
    {
        m_verts[i].color.a = i * (255.f / (m_verts.size()-1));
    }
}

void Trail::draw()
{
    Renderer.drawScaled(m_verts.data(), m_verts.size(), sf::LineStrip);
}

void Trail::setPosition(const vec2& pos)
{
    m_pos = pos;

    if (!m_verts.empty())
        m_verts.back().position = m_pos;
}

void Trail::setColor(const sf::Color& color)
{
    m_color = color;
}

void Trail::setInterval(float interval)
{
    m_interval = interval;
}