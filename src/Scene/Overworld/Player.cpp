#include "Player.hpp"
#include "Scene/Scene.hpp"
#include "Bullet.hpp"
#include "Renderer.hpp"
#include "Physics/PhysicsWorld.hpp"
#include "Drone.hpp"
#include "Hud.hpp"

static constexpr float HeatRegen = 100.f;
static constexpr float MoveHeatCost = 8.f;
static constexpr float ShootHeatCost = 2.f;
static constexpr float LaserHeatCost = 50.f; //per second

Player::Player(Scene* scene)
    : SceneObject(scene)
{
    m_name = "player_ship";
    m_body = m_scene->getPhysicsWorld()->addRigidBody({0,0}, true);
    m_body->setUserData(this);

    // if (sf::Joystick::isConnected(0))
        // printf("gamepad@\n");

    printf("button count %d\n", sf::Joystick::getButtonCount(0));
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
    // for (int i = 0; i < 16; i++)
    // {
    //     if (sf::Joystick::isButtonPressed(0, i))
    //         printf("%d is pressed!\n", i);
    // }

    // printf("%f %f\n", sf::Joystick::getAxisPosition(0, sf::Joystick::PovX), sf::Joystick::getAxisPosition(0, sf::Joystick::PovY));

    if (m_overheat) return;

    float ex = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
    float ey = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

    vec2 mov = vec2(ex, ey);
    m_aim += (mov * 0.2f) * timer::delta;
    // m_aim = math::normalize(m_aim);
    // m_aim *= 10.f;

    m_body->rotateTowards(m_pos + m_aim, 200 * timer::delta);

    float speed = (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) ? 8.f : 4.f;

    // if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    if (sf::Joystick::isButtonPressed(0, 4))
    {
        m_body->applyLinearImpulse(m_body->getDirection() * timer::delta * speed);
        exertHeat(speed * 2 * timer::delta);
    }

    Renderer::get().setZoom(math::length(m_body->getLinearVelocity()));
}

void Player::shoot()
{
    if (m_overheat) return;

    // if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    if (sf::Joystick::isButtonPressed(0, 5))
    {
        vec2 pos = m_body->getPosition();
        // vec2 dir = math::normalize(Renderer::get().getGlobalMousePosition() - pos);
        vec2 dir = math::normalize(m_aim);

        switch (m_weapon)
        {
            case Weapon::BASIC:
            {
                if (m_shootTimer.getElapsedTime() < sf::milliseconds(100))
                    return;

                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection(), true);

                exertHeat(ShootHeatCost);
                m_shootTimer.restart();
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

                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() + (side * 0.25f), true);
                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() - (side * 0.25f), true);

                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() + (side * 0.5f), true);
                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() - (side * 0.5f), true);

                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() + (side * 0.75f), true);
                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() - (side * 0.75f), true);

                exertHeat(ShootHeatCost);
                m_shootTimer.restart();
            }
            break;
            case Weapon::LASER:
            {
                RaycastCallback result;
                // m_scene->getPhysicsWorld()->castRay(&result, m_body->getPosition(), Renderer::get().getGlobalMousePosition());

                vec2 target = m_pos + (m_aim * 100.f);

                if (!isnan(target.x) and !isnan(target.y))
                {
                    // printf("target %f %f\n", target.x, target.y);
                    m_scene->getPhysicsWorld()->castRay(&result, m_body->getPosition(), target);

                    m_rayhit = {result.point.x, result.point.y};

                    if (m_shootTimer.getElapsedTime() > sf::milliseconds(25) && result.hasHit)
                    {
                        if (result.object)
                        if (result.object->getName() == "drone")
                        {
                            auto drone = result.object->as<Drone>();
                            drone->damage(7);
                        }

                        m_shootTimer.restart();
                    }

                    exertHeat(timer::delta * 50);
                }
            }
            break;
        }
    }
}

void Player::update(float dt)
{
    control();
    shoot();

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    if (sf::Joystick::isButtonPressed(0, 0))
        m_weapon = Weapon::BASIC;
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    if (sf::Joystick::isButtonPressed(0, 1))
        m_weapon = Weapon::SHOTGUN;
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    if (sf::Joystick::isButtonPressed(0, 2))
        m_weapon = Weapon::LASER;

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

    // if (m_weapon == Weapon::LASER && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    if (m_weapon == Weapon::LASER && sf::Joystick::isButtonPressed(0, 5))
    {
        Renderer::get().drawLineScaled(m_rayhit + vec2(1,0), m_rayhit + vec2(-1,0), sf::Color::Blue);
        Renderer::get().drawLineScaled(m_rayhit + vec2(0,1), m_rayhit + vec2(0,-1), sf::Color::Blue);

        Renderer::get().drawLineScaled(m_pos, m_pos + (m_aim * 100.f), sf::Color::Red);
    }

    Renderer::get().drawLineScaled(m_pos + m_aim + vec2(1,0), m_pos + m_aim + vec2(-1,0), sf::Color::Blue);
    Renderer::get().drawLineScaled(m_pos + m_aim + vec2(0,1), m_pos + m_aim + vec2(0,-1), sf::Color::Blue);

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