#include "Trail.hpp"
#include "Core/Timer.hpp"
#include "Renderer.hpp"

void Trail::update()
{
    m_timer += sf::seconds(timer::delta);

    if (m_timer > sf::seconds(m_interval))
    {
        m_points.push_back(m_pos);
        m_timer = sf::seconds(0);
    }

    if (m_points.size() > m_length)
        m_points.erase(m_points.begin());
}

void Trail::draw()
{
    m_verts.clear();

    for (int i = 0; i < m_points.size(); i++)
    {
        if (i == 0)
        {
            sf::Vertex last = sf::Vertex(m_points[0], sf::Color::Transparent);
            m_verts.push_back(last);
            m_verts.push_back(last);
        }
        else
        {
            const float width = 0.07;
            sf::Vertex vs[2];

            vec2 diff = math::normalize(m_points[i] - m_points[i-1]) * width;
            vs[0].position = vec2(-diff.y, diff.x) + m_points[i];
            vs[1].position = vec2(diff.y, -diff.x) + m_points[i];

            vs[0].color = m_color;
            vs[1].color = m_color;

            vs[0].color.a = i * (255.f / (m_points.size()-1));
            vs[1].color.a = i * (255.f / (m_points.size()-1));

            m_verts.push_back(vs[0]);
            m_verts.push_back(vs[1]);
        }
    }


    Renderer.drawScaled(m_verts.data(), m_verts.size(), sf::TriangleStrip);
}

void Trail::setPosition(const vec2& pos)
{
    m_pos = pos;

    if (!m_points.empty())
        m_points.back() = m_pos;
}

void Trail::setLength(int length)
{
    m_length = length;
}

void Trail::setColor(const sf::Color& color)
{
    m_color = color;
}

void Trail::setInterval(float interval)
{
    m_interval = interval;
}