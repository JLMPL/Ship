#include "Bullet.hpp"
#include "Scene/Scene.hpp"
#include "Renderer.hpp"
#include "Physics/PhysicsWorld.hpp"

Bullet::Bullet(Scene* scene)
    : SceneObject(scene)
{
}

void Bullet::ready(const vec2& pos, const vec2& dir, bool player)
{
    m_body = m_scene->getPhysicsWorld()->spawnBullet(pos, dir * 10.f, player);
    m_body->setUserData((void*)this);
    m_clock = sf::seconds(0);

    m_name = (player) ? "player_bullet" : "enemy_bullet";
}

void Bullet::update(float dt)
{
    m_clock += sf::seconds(0);

    if (m_body)
        m_pos = m_body->getPosition();

    if (m_clock > sf::seconds(1))
        destroy();
}

void Bullet::draw()
{

}

void Bullet::onContact(SceneObject* other)
{
    if (other)
        destroy();
}