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
#include "Random.hpp"

Drone::Drone(Scene* scene)
    : Enemy(scene)
{
    m_name = "drone";

    std::vector<vec2> points(3);
    points[0] = {-1.f, 0.6};
    points[1] = {1., 0};
    points[2] = {-1.f, -0.6};

    m_body = m_scene->getPhysicsWorld()->addRigidBody({0,0}, false, points);

    m_player = m_scene->findObject("player_ship");
    m_clock = sf::seconds(rng::inRange(0.f,1.f));

    m_healthbar.setMaxValue(m_maxHealth);
    m_healthbar.setValue(m_maxHealth);

    m_mesh.loadFromFile("data/meshes/drone.obj");

    m_moneyValue = 75;
    m_color = sf::Color(128,0,0);
}

void Drone::ready(const vec2& spawnPoint)
{
    Spacecraft::ready(false);
    m_trail.setColor(sf::Color::Red);
    m_spawnPoint = spawnPoint;
    Audio.setVolume(_Audio::EFFECT_ENEMY_BLASTER, 0.5);

    m_mesh.setScale(0.7f);
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
