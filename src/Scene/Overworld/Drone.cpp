#include "Drone.hpp"
#include "Scene/Scene.hpp"
#include "Renderer.hpp"
#include "Physics/PhysicsWorld.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Core/Timer.hpp"
#include <algorithm>
#include "GameplayVars.hpp"
#include "Audio/Audio.hpp"

Drone::Drone(Scene* scene)
    : Spacecraft(scene)
{
    m_name = "drone";

    m_player = m_scene->findObject("player_ship");
    m_clock = sf::seconds(0);

    m_healthbar.setMaxValue(m_maxHealth);
    m_healthbar.setValue(m_maxHealth);

    m_mesh.loadFromFile("data/meshes/drone.obj");
}

void Drone::ready(const vec2& spawnPoint)
{
    Spacecraft::ready(false);
    m_trail.setColor(sf::Color::Red);
    m_spawnPoint = spawnPoint;
    Audio.setVolume(_Audio::EFFECT_ENEMY_BLASTER, 0.5);
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
            vec2 dir = math::normalize(Renderer.getGlobalMousePosition() - pos);
            m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection(), DroneDamage, false);

            Audio.playSound(_Audio::EFFECT_ENEMY_BLASTER);

            m_clock = sf::seconds(0);
        }
    }
    else
        towards = m_spawnPoint;

    float dist = math::distance(m_body->getPosition(), towards);

    if (dist > 10)
        thrust(m_body->getDirection() * timer::delta * 1.f);
    else if (dist < 3)
        m_body->applyLinearImpulse(-m_body->getDirection() * timer::delta * 1.f);

    m_body->rotateTowards(towards, 100 * dt);

    m_pos = m_body->getPosition();
    m_healthbar.setPosition(m_pos - m_healthbar.getSize() /2.f);

    Spacecraft::update(dt);
}

void Drone::draw()
{
    Spacecraft::draw();
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
            m_player->as<Player>()->addMoney(DroneXpValue);
            m_isDead = false;
        }
        destroy();
    }

    m_healthbar.setValue(m_health);
}
