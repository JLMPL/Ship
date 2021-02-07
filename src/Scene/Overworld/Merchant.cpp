#include "Merchant.hpp"
#include "Scene/Scene.hpp"
#include "Renderer.hpp"
#include "Physics/PhysicsWorld.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Core/Timer.hpp"
#include <algorithm>
#include "GameplayVars.hpp"

Merchant::Merchant(Scene* scene)
    : Spacecraft(scene)
{
    m_name = "merchant";

    m_player = m_scene->findObject("player_ship");

    m_maxHealth = 1000;
    m_health = 1000;
    m_healthbar.setMaxValue(m_maxHealth);
    m_healthbar.setValue(m_maxHealth);

    m_mesh.loadFromFile("data/merchant.obj");
}

void Merchant::ready(const vec2& spawnPoint)
{
    Spacecraft::ready(false);
    m_trail.setColor(sf::Color::Yellow);
    m_spawnPoint = spawnPoint;
}

void Merchant::update(float dt)
{
    vec2 dir = math::normalize(m_body->getPosition() - m_player->getPosition());
    float dist = math::length(m_body->getPosition() - m_player->getPosition());

    m_body->rotateTowards(m_body->getPosition() + dir, 100 * dt);

    if (dist < 40)
        m_body->applyLinearImpulse(dir * timer::delta * 0.8f);
    else
        m_body->applyLinearImpulse(-dir * timer::delta * 1.f);

    m_pos = m_body->getPosition();
    m_healthbar.setPosition(m_pos);

    Spacecraft::update(dt);
}

void Merchant::draw()
{
    Spacecraft::draw();
    m_healthbar.draw();
}

void Merchant::onContact(SceneObject* other)
{
    if (!other) return;

    if (other->getName() == "player_bullet")
    {
        damage(other->as<Bullet>()->getDamage());
    }
}

void Merchant::damage(int value)
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
