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
    m_body = m_scene->getPhysicsWorld()->spawnBullet(pos, dir, player);
    m_clock.restart();
}

void Bullet::update(float dt)
{
    if (m_body)
        m_pos = m_body->getPosition();

    if (m_clock.getElapsedTime() > sf::seconds(1))
        destory();
}

void Bullet::draw()
{

}
