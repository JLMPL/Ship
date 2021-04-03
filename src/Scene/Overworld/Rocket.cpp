#include "Rocket.hpp"
#include "Scene/Scene.hpp"
#include "Renderer.hpp"
#include "Spacecraft.hpp"
#include "Explosion.hpp"
#include "Audio/Audio.hpp"

Rocket::Rocket(Scene* scene)
	: SceneObject(scene)
{
    m_name = "rocket";

    m_mesh.loadFromFile("data/meshes/rocket.obj");
    m_mesh.setScale(0.5f);
}

void Rocket::ready(const vec2& pos, const vec2& dir)
{
    m_pos = pos;
    m_dir = dir;
    m_timer = sf::seconds(0.f);
    m_trail.setInterval(0.005f);
    m_trail.setLength(20);
}

void Rocket::update(float dt)
{
    m_pos += m_dir * m_acceleration * dt;

    if (!m_target)
    {
        m_timer += sf::seconds(dt);

        if (m_timer > sf::seconds(1.f))
        {
            m_scene->spawnObject<Explosion>(m_pos, sf::Color::White);
            Audio.playSound(_Audio::EFFECT_BIG_EXPLOSION);
            destroy();
        }
    }

    if (!m_attacking)
    {
        m_acceleration = std::max(10.f, m_acceleration - dt * 120.f);

        if (m_acceleration == 10.f)
        {
            m_attacking = true;
        }
    }
    else
    {
        m_acceleration = std::min(40.f, m_acceleration + dt * 20.f);

        m_target = m_scene->findClosestObjectByName(m_pos, "kamikaze");

        if (!m_target)
            m_target = m_scene->findClosestObjectByName(m_pos, "drone");

        if (!m_target)
            m_target = m_scene->findClosestObjectByName(m_pos, "gunner");

        if (!m_target)
            m_target = m_scene->findClosestObjectByName(m_pos, "merchant");

        if (m_target)
        {
            m_dir += math::normalize(m_target->getPosition() - m_pos) * (m_acceleration / 20.f);
            m_dir = math::normalize(m_dir);

            if (math::distance(m_target->getPosition(), m_pos) < 1.f)
            {
                m_target->as<Spacecraft>()->damage(50);
                m_scene->spawnObject<Explosion>(m_pos, sf::Color::White);
                Audio.playSound(_Audio::EFFECT_BIG_EXPLOSION);
                destroy();
            }
        }
    }

    m_trail.setPosition(m_pos);
    m_trail.update();

    m_mesh.setRotation(-atan2(m_dir.x, m_dir.y) + M_PI);
    m_mesh.setPosition(m_pos);
}

void Rocket::draw()
{
    m_trail.draw();
    m_mesh.draw();
}