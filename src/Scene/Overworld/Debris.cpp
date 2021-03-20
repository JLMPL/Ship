#include "Debris.hpp"
#include "Scene/Scene.hpp"
#include "Random.hpp"

Debris::Debris(Scene* scene)
 : SceneObject(scene)
{
    m_mesh.loadFromFile("data/meshes/debris.obj");
}

void Debris::ready(const vec2& pos, const sf::Color& color)
{
    m_pos = pos;
    m_mesh.setColor(color);
    m_dir = math::normalize(vec2(rng::inRange(-1,1), rng::inRange(-1,1)));
    m_rotationSpeed = rng::inRange(-20,20);
    m_fallSpeed = rng::inRange(0.2,1);
}

void Debris::update(float dt)
{
    m_scale = std::max(0.f, m_scale - dt * m_fallSpeed);

    if (m_scale <= 0.f)
        destroy();

    m_pos += m_dir * dt * 5.f;
    m_angle += m_rotationSpeed * dt;

    m_mesh.setRotation(m_angle);
    m_mesh.setScale(m_scale);
    m_mesh.setPosition(m_pos);
}

void Debris::draw()
{
    m_mesh.draw();
}
