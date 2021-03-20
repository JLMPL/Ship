#include "Merchant.hpp"
#include "Scene/Scene.hpp"
#include "Renderer.hpp"
#include "Physics/PhysicsWorld.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "Core/Timer.hpp"
#include <algorithm>
#include "GameplayVars.hpp"
#include "Random.hpp"

Merchant::Merchant(Scene* scene)
    : Enemy(scene)
{
    m_name = "merchant";

    std::vector<vec2> points(3);
    points[0] = vec2(-1.f, 0.6) * 1.429f;
    points[1] = vec2(1., 0) * 1.429f;
    points[2] = vec2(-1.f, -0.6) * 1.429f;

    m_body = m_scene->getPhysicsWorld()->addRigidBody({0,0}, false, points);

    m_player = m_scene->findObject("player_ship");

    m_maxHealth = 1000;
    m_health = 1000;
    m_healthbar.setMaxValue(m_maxHealth);
    m_healthbar.setValue(m_maxHealth);

    m_mesh.loadFromFile("data/meshes/merchant.obj");
	m_target = vec2(rng::inRange(-250.f, 250.f), rng::inRange(-250.f, 250.f));

    m_moneyValue = 250;
    m_color = sf::Color(128,128,0);
}

void Merchant::ready(const vec2& spawnPoint)
{
    Enemy::ready(false);
    m_trail.setColor(sf::Color::Yellow);
    m_spawnPoint = spawnPoint;
}

void Merchant::update(float dt)
{
    if (m_pos.x > 700.f || m_pos.x < -700.f || m_pos.y < -700.f || m_pos.y > 700.f)
    {
        m_body->rotateTowards(vec2(0,0), 200 * timer::delta);
        thrust(m_body->getDirection() * timer::delta * 10.f);
    }
    else
    {
    	if (math::distance(m_target, m_body->getPosition()) < 25.f)
    	{
    		m_target = vec2(rng::inRange(-250.f, 250.f), rng::inRange(-250.f, 250.f));
    	}

        vec2 dir = math::normalize(m_target - m_body->getPosition());

        m_body->rotateTowards(m_body->getPosition() + dir, 100 * dt);

    	if (math::length(m_body->getLinearVelocity()) < 25.f)
    		thrust(dir * timer::delta * 5.f);
    }

    m_pos = m_body->getPosition();
    m_healthbar.setPosition(m_pos - m_healthbar.getSize()/2.f);

    Enemy::update(dt);
}
