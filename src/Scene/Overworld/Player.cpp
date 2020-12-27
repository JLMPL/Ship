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
    m_body = m_scene->getPhysicsWorld()->addRigidBody({0,0}, true);
    m_body->setUserData(this);
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

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        vec2 pos = m_body->getPosition();
        vec2 dir = math::normalize(Renderer::get().getGlobalMousePosition() - pos);

        switch (m_weapon)
        {
            case Weapon::BASIC:
            {
                if (m_shootTimer.getElapsedTime() < sf::milliseconds(100))
                    return;

                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection(), true);
            }
            break;
            case Weapon::SHOTGUN:
            {
                if (m_shootTimer.getElapsedTime() < sf::seconds(0.5))
                    return;

                vec2 side = vec2(dir.y, -dir.x) * 0.25f;

                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection(), true);
                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() + side, true);
                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() - side, true);

                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() + (side * 0.5f), true);
                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() - (side * 0.5f), true);
            }
            break;
        }

        exertHeat(ShootHeatCost);
        m_shootTimer.restart();
    }
}

void Player::update(float dt)
{
    control();
    shoot();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        m_weapon = Weapon::BASIC;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        m_weapon = Weapon::SHOTGUN;

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

void Player::setPosition(const vec2& pos)
{
    m_body->setPosition(pos);
}

void Player::onContact(SceneObject* other)
{
    if (!other) return;

    if (other->getName() == "enemy_bullet")
    {
        m_health = std::max(0, --m_health);
    }
}