#include "Kamikaze.hpp"
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
#include "Explosion.hpp"
#include "Debris.hpp"

Kamikaze::Kamikaze(Scene* scene)
    : Enemy(scene)
{
    m_name = "kamikaze";

    std::vector<vec2> points(3);
    points[0] = {-0.5f, 0.3};
    points[1] = {0.5f, 0};
    points[2] = {-0.5f, -0.3};

    m_body = m_scene->getPhysicsWorld()->addRigidBody({0,0}, false, points);

    m_player = m_scene->findObject("player_ship");

    m_healthbar.setMaxValue(m_maxHealth);
    m_healthbar.setValue(m_maxHealth);

    m_mesh.loadFromFile("data/meshes/drone.obj");

    m_maxHealth = 1;
    m_health = 1;

    m_moneyValue = 100;
    m_color = sf::Color(0,128,128);
}

void Kamikaze::ready(const vec2& spawnPoint)
{
    Spacecraft::ready(false);
    m_trail.setColor(sf::Color(0,255,255));
    m_trail.setInterval(0.001);
    m_spawnPoint = spawnPoint;
    Audio.setVolume(_Audio::EFFECT_ENEMY_BLASTER, 0.5);

    m_mesh.setScale(0.7f/2.f);
}

void Kamikaze::update(float dt)
{
    vec2 towards = m_player->getPosition();

    vec2 aim = math::normalize(towards - m_body->getPosition());

    float dot = math::dot(m_body->getDirection(), aim);

    if (math::distance(m_body->getPosition(), m_player->getPosition()) < 50.f)
        // dot > 0.9)
        // math::length(m_body->getLinearVelocity()) < 10.f)
    {
        // thrust(m_body->getDirection() * timer::delta * 5.f);
        m_body->applyLinearImpulse(aim * timer::delta * 5.f);
    }
    else
        m_body->fullStop();

    m_body->rotateTowards(towards, 300 * dt);

    m_pos = m_body->getPosition();
    m_healthbar.setPosition(m_pos - m_healthbar.getSize() /2.f);

    Spacecraft::update(dt);
}

void Kamikaze::onContact(SceneObject* other)
{
    Spacecraft::onContact(other);

    if (!other) return;

    if (other->getName() == "player_ship")
    {
        m_scene->spawnObject<Explosion>(m_body->getPosition(), sf::Color(0,255,255));

        for (int i = 0; i < 10; i++)
            m_scene->spawnObject<Debris>(m_pos, m_color);

        destroy();
    }
}
