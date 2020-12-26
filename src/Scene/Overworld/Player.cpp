#include "Player.hpp"
#include "Scene/Scene.hpp"
#include "Bullet.hpp"
#include "Renderer.hpp"
#include "Physics/PhysicsWorld.hpp"
#include "Hud.hpp"

static constexpr float HeatRegen = 100.f;
static constexpr float MoveHeatCost = 8.f;
static constexpr float ShootHeatCost = 4.f;

Player::Player(Scene* scene)
    : SceneObject(scene)
{
    m_name = "player_ship";
    m_body = m_scene->getPhysicsWorld()->addRigidBody({0,0}, false);

    m_body->applyLinearImpulse({1,0});
}

void Player::ready()
{
    m_hud = m_scene->findObject("hud")->as<Hud>();
}

void Player::exertHeat(float hdiff)
{
    m_heat = std::min(m_heat + hdiff, 100.f);

    if (m_heat >= 100.f)
        m_overheat = true;

    m_heatTimer.restart();
}

void Player::control()
{
    if (m_overheat) return;

    m_body->rotateTowards(Renderer::get().getGlobalMousePosition(), 200 * timer::delta);

    float speed = (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) ? 8.f : 2.f;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        m_body->applyLinearImpulse(m_body->getDirection() * timer::delta * speed);
        exertHeat(speed * 2 * timer::delta);
    }

    Renderer::get().setZoom(math::length(m_body->getLinearVelocity()));
}

void Player::shoot()
{
    if (m_overheat) return;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_shootTimer.getElapsedTime().asMilliseconds() > 250)
    {
        vec2 pos = m_body->getPosition();
        vec2 dir = math::normalize(Renderer::get().getGlobalMousePosition() - pos);

        Bullet* bullet = m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection(), true);
        // bullet->ready();

        exertHeat(ShootHeatCost);
        m_shootTimer.restart();
    }
}

void Player::update(float dt)
{
    control();
    shoot();

    if (m_heatTimer.getElapsedTime() > sf::seconds(0.5))
    {
        m_heat = std::max(m_heat - timer::delta * HeatRegen, 0.f);

        if (m_heat == 0.f)
            m_overheat = false;
    }

    m_hud->setPlayerCoords(m_pos.x, m_pos.y);
    m_hud->setHeat(m_heat);
    m_hud->setHealthPercentage(float(m_health) / float(m_maxHealth));

    m_pos = m_body->getPosition();
}

void Player::draw()
{
    Renderer::get().setView(m_pos);
}
