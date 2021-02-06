#include "Drone.hpp"
#include "Scene/Scene.hpp"
#include "Renderer.hpp"
#include "Physics/PhysicsWorld.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Core/Timer.hpp"
#include <algorithm>
#include "GameplayVars.hpp"

Drone::Drone(Scene* scene)
    : SceneObject(scene)
{
    m_body = m_scene->getPhysicsWorld()->addRigidBody({0,0}, false);
    m_body->setUserData((void*)this);

    m_name = "drone";

    m_player = m_scene->findObject("player_ship");
    m_clock = sf::seconds(0);

    m_healthbar.setMaxValue(m_maxHealth);
    m_healthbar.setValue(m_maxHealth);

    m_mesh.loadFromFile("data/drone.obj");
}

void Drone::ready(const vec2& spawnPoint)
{
    m_spawnPoint = spawnPoint;
}

void Drone::update(float dt)
{
    m_clock += sf::seconds(dt);

    vec2 towards = m_player->getPosition();
    if (math::distance(m_body->getPosition(), m_player->getPosition()) < 25.f)
    {
        if (m_clock > sf::seconds(1))
        {
            vec2 pos = m_body->getPosition();
            vec2 dir = math::normalize(Renderer::get().getGlobalMousePosition() - pos);
            m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection(), DroneDamage, false);

            m_clock = sf::seconds(0);
        }
    }
    else
        towards = m_spawnPoint;

    float dist = math::distance(m_body->getPosition(), towards);

    if (dist > 10)
        m_body->applyLinearImpulse(m_body->getDirection() * timer::delta * 1.f);
    else if (dist < 3)
        m_body->applyLinearImpulse(-m_body->getDirection() * timer::delta * 1.f);

    m_body->rotateTowards(towards, 100 * dt);

    m_pos = m_body->getPosition();
    m_healthbar.setPosition(m_pos);
}

void Drone::draw()
{
    m_mesh.setPosition(m_pos);
    m_mesh.setOffset(vec2(0, 0.2));
    m_mesh.setRotation(m_body->getAngle() + M_PI/2);
    m_mesh.setScale(0.7f);

    m_mesh.draw();
    m_healthbar.draw();
}

void Drone::onContact(SceneObject* other)
{
    if (!other) return;

    if (other->getName() == "player_bullet")
    {
        damage(other->as<Bullet>()->getDamage());
    }
}

void Drone::damage(int value)
{
    m_health = std::max(0, m_health - value);

    if (m_health == 0)
    {
        if (!m_isDead)
        {
            m_player->as<Player>()->addXp(DroneXpValue);
            m_isDead = false;
        }
        destroy();
    }

    m_healthbar.setValue(m_health);
}

void Drone::setPosition(const vec2& pos)
{
    m_body->setPosition(pos);
}