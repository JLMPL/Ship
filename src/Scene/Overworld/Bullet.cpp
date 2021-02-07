#include "Bullet.hpp"
#include "Scene/Scene.hpp"
#include "Renderer.hpp"
#include "Physics/PhysicsWorld.hpp"

Bullet::Bullet(Scene* scene)
    : SceneObject(scene)
{
}

void Bullet::ready(const vec2& pos, const vec2& dir, int damage, bool player)
{
    m_body = m_scene->getPhysicsWorld()->spawnBullet(pos, dir * 10.f, player);
    m_body->setUserData((void*)this);
    m_clock = sf::seconds(0);

    m_damage = damage;

    if (player)
    {
        m_name = "player_bullet";
        m_trail.setColor(sf::Color::White);
    }
    else
    {
        m_name = "enemy_bullet";
        m_trail.setColor(sf::Color::Red);
    }

    m_trail.setInterval(0.01);
}

void Bullet::update(float dt)
{
    m_body->setEnabled(m_enabled);
    m_clock += sf::seconds(dt);

    if (m_body)
        m_pos = m_body->getPosition();

    if (m_clock > sf::seconds(10))
        destroy();

    m_trail.update();
    m_trail.setPosition(m_body->getPosition());
}

void Bullet::draw()
{
    m_trail.draw();
}

void Bullet::onContact(SceneObject* other)
{
    if (other)
    {
        m_enabled = false;
    }
}

int Bullet::getDamage() const
{
    return m_damage;
}