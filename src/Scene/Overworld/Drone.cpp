#include "Drone.hpp"
#include "Scene/Scene.hpp"
#include "Renderer.hpp"
#include "Physics/PhysicsWorld.hpp"
#include "Bullet.hpp"
#include "Core/Timer.hpp"
#include <algorithm>

Drone::Drone(Scene* scene)
    : SceneObject(scene)
{
    m_body = m_scene->getPhysicsWorld()->addRigidBody({0,0}, false);
    m_body->setUserData((void*)this);

    m_player = m_scene->findObject("player_ship");
    m_clock.restart();

    m_healthbar.setMaxValue(m_maxHealth);
}

void Drone::update(float dt)
{
    if (m_clock.getElapsedTime() > sf::seconds(1))
    {
        vec2 pos = m_body->getPosition();
        vec2 dir = math::normalize(Renderer::get().getGlobalMousePosition() - pos);
        m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection(), false);

        m_clock.restart();
    }

    if (m_player)
    {
        float dist = math::distance(m_body->getPosition(), m_player->getPosition());

        if (dist > 10)
            m_body->applyLinearImpulse(m_body->getDirection() * timer::delta * 1.f);
        else if (dist < 3)
            m_body->applyLinearImpulse(-m_body->getDirection() * timer::delta * 1.f);


        m_body->rotateTowards(m_player->getPosition(), 100 * dt);
    }
    else
        m_body->rotateTowards(vec2(0,0), 100 * dt);


    m_pos = m_body->getPosition();
    m_healthbar.setPosition(m_pos);
}

void Drone::draw()
{
    m_healthbar.draw();
}

void Drone::onContact(SceneObject* other)
{
    if (!other) return;

    if (other->getName() == "player_bullet")
    {
        m_health = std::max(0, --m_health);

        if (m_health == 0)
            destroy();

        m_healthbar.setValue(m_health);
    }
}