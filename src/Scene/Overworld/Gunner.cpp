#include "Gunner.hpp"
#include "Scene/Scene.hpp"
#include "Renderer.hpp"
#include "Physics/PhysicsWorld.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Core/Timer.hpp"
#include <algorithm>
#include "GameplayVars.hpp"
#include "Audio/Audio.hpp"

Gunner::Gunner(Scene* scene)
    : Enemy(scene)
{
    m_name = "gunner";

    m_maxHealth = 250;
    m_health = m_maxHealth;

    m_healthbar.setMaxValue(m_maxHealth);
    m_healthbar.setValue(m_maxHealth);

    m_mesh.loadFromFile("data/meshes/gunner.obj");

    m_moneyValue = 150;
}

void Gunner::ready(const vec2& spawnPoint)
{
    Spacecraft::ready(false);
    m_trail.setColor(sf::Color(192,0,192));
    m_spawnPoint = spawnPoint + vec2(1,1);
    Audio.setVolume(_Audio::EFFECT_ENEMY_BLASTER, 0.5);
    m_player = m_scene->findObject("player_ship");
}

void Gunner::shoot()
{
    if (m_shootTimer > sf::seconds(0.1))
    {
        auto bullet = m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection(), DroneDamage, false);
        bullet->setColor(sf::Color(192,0,192));
        m_shootTimer = sf::seconds(0);
    }
}

void Gunner::update(float dt)
{
    m_shootTimer += sf::seconds(dt);
    m_stateTimer += sf::seconds(dt);

    if (math::distance(m_pos, m_spawnPoint) > 15.f)
    {
        vec2 direction = math::normalize(m_spawnPoint - m_body->getPosition());
        m_body->applyLinearImpulse(direction * timer::delta * 1.f);
    }

    m_body->rotateTowards(m_player->getPosition(), 200 * dt);

    if (m_stateTimer > sf::seconds(5))
    {
        m_isShooting = !m_isShooting;
        m_stateTimer = sf::seconds(0);
    }

    if (m_isShooting && math::distance(m_pos, m_player->getPosition()) < 100.f)
        shoot();

    m_pos = m_body->getPosition();
    m_healthbar.setPosition(m_pos - m_healthbar.getSize() /2.f);

    Spacecraft::update(dt);
}
