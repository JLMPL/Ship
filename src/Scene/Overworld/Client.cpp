#include "Client.hpp"
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

Client::Client(Scene* scene)
    : Enemy(scene)
{
    m_name = "client";

    std::vector<vec2> points(3);
    points[0] = {-1.f, 0.6};
    points[1] = {1., 0};
    points[2] = {-1.f, -0.6};

    m_body = m_scene->getPhysicsWorld()->addRigidBody({0,0}, true, points, true);

    m_player = m_scene->findObject("player_ship");

    m_maxHealth = 2000;
    m_health = m_maxHealth;

    m_healthbar.setMaxValue(m_maxHealth);
    m_healthbar.setValue(m_maxHealth);

    m_mesh.loadFromFile("data/meshes/client.obj");

    m_moneyValue = 0;
    m_color = sf::Color(128,128,0);
}

void Client::ready(const vec2& spawnPoint)
{
    Spacecraft::ready(false);
    m_trail.setColor(sf::Color(255,255,0));
    m_spawnPoint = spawnPoint;
    Audio.setVolume(_Audio::EFFECT_ENEMY_BLASTER, 0.5);

    m_mesh.setScale(0.7f);
}

void Client::update(float dt)
{
    vec2 towards = m_player->getPosition();
    float dist = math::distance(m_body->getPosition(), towards);

    // if (dist > 10)
    //     thrust(m_body->getDirection() * timer::delta * 1.f);
    // else if (dist < 3)
    //     m_body->applyLinearImpulse(-m_body->getDirection() * timer::delta * 2.f);

    if (m_goAway)
    {
        vec2 farFarAway = vec2(1000,1000);
        m_body->rotateTowards(farFarAway, 100 * dt);
        thrust(m_body->getDirection() * timer::delta * 100.f);

        if (math::distance(m_player->getPosition(), m_pos) > 200.f)
            kill();
    }
    else
        m_body->rotateTowards(towards, 100 * dt);

    m_pos = m_body->getPosition();
    m_healthbar.setPosition(m_pos - m_healthbar.getSize() /2.f);

    Spacecraft::update(dt);
}

void Client::onContact(SceneObject* other)
{
    if (!other) return;

    if (other->getName() == "enemy_bullet")
    {
        damage(other->as<Bullet>()->getDamage());
    }
}

void Client::goAway()
{
    m_goAway = true;
}