#include "Rocket.hpp"
#include "Scene/Scene.hpp"
#include "Renderer.hpp"
#include "Spacecraft.hpp"

Rocket::Rocket(Scene* scene)
	: SceneObject(scene)
{
    m_name = "rocket";
}

void Rocket::ready(const vec2& pos, const vec2& dir)
{
    m_pos = pos;
    m_dir = dir;
    m_timer = sf::seconds(0.f);
}

void Rocket::update(float dt)
{
    m_pos += m_dir * m_acceleration * dt;

    if (!m_target)
    {
        m_timer += sf::seconds(dt);

        if (m_timer > sf::seconds(1.f))
            destroy();
    }

    if (!m_attacking)
    {
        m_acceleration = std::max(0.f, m_acceleration - dt * 120.f);

        if (m_acceleration == 0.f)
        {
            m_attacking = true;
        }
    }
    else
    {
        m_acceleration = std::min(40.f, m_acceleration + dt * 30.f);

        m_target = m_scene->findClosestObjectByName(m_pos, "drone");

        if (m_target)
        {
            m_dir += math::normalize(m_target->getPosition() - m_pos) * (m_acceleration / 20.f);
            m_dir = math::normalize(m_dir);

            if (math::distance(m_target->getPosition(), m_pos) < 1.f)
            {
                m_target->as<Spacecraft>()->damage(50);
                destroy();
            }
        }
    }
}

void Rocket::draw()
{
    sf::Vertex verts[2] = {
        sf::Vertex(m_pos, sf::Color::White),
        sf::Vertex(m_pos + m_dir, sf::Color::White)
    };
    Renderer.drawScaled(verts, 2, sf::Lines);
}