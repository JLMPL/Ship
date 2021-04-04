#include "Mothership.hpp"
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
#include "Kamikaze.hpp"

Mothership::Mothership(Scene* scene)
    : Enemy(scene)
{
    m_name = "mothership";

    std::vector<vec2> points =
    {
        vec2(1.38925f, -0.f) * 3.f,
        vec2(1.26328f, -0.378901f) * 3.f,
        vec2(0.f, -0.872088f) * 3.f,
        vec2(-1.26328f, -0.378901f) * 3.f,
        vec2(-1.38925f, -0.f) * 3.f,
        vec2(1.26328f, 0.378901f) * 3.f,
        vec2(0.f, 0.872088f) * 3.f,
        vec2(-1.26328f, 0.378901f) * 3.f,
    };

    m_body = m_scene->getPhysicsWorld()->addRigidBody({0,0}, false, points);

    m_player = m_scene->findObject("player_ship");
    m_clock = sf::seconds(rng::inRange(0.f,1.f));

    m_maxHealth = 1000;
    m_health = 1000;

    m_healthbar.setMaxValue(m_maxHealth);
    m_healthbar.setValue(m_maxHealth);

    m_mesh.loadFromFile("data/meshes/mothership.obj");

    m_moneyValue = 1000;
    m_color = sf::Color(128,128,128);
}

void Mothership::ready(const vec2& spawnPoint)
{
    Spacecraft::ready(false);
    m_trail.setColor(sf::Color::Red);
    m_spawnPoint = spawnPoint;

    m_mesh.setScale(3.f);
}

void Mothership::update(float dt)
{
    m_clock += sf::seconds(dt);

    if (m_clock > sf::seconds(10))
    {
        for (int i = 0; i < 2; i++)
        {
            auto dr = m_scene->spawnObject<Kamikaze>(m_pos);
            dr->setPosition(m_pos);
        }
        m_clock = sf::seconds(0);
    }

    // m_body->applyLinearImpulse(-m_body->getDirection() * timer::delta * 1.f);

    m_body->rotateTowards(vec2(0,1), 100 * dt);

    m_pos = m_body->getPosition();
    m_healthbar.setPosition(m_pos - m_healthbar.getSize() /2.f);

    Spacecraft::update(dt);
}
