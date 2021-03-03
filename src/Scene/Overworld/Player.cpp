#include "Player.hpp"
#include "Scene/Scene.hpp"
#include "Bullet.hpp"
#include "Renderer.hpp"
#include "Physics/PhysicsWorld.hpp"
#include "Input/Input.hpp"
#include "Drone.hpp"
#include "Hud.hpp"
#include "GameplayVars.hpp"
#include "Scene/Tutorial.hpp"
#include "Audio/Audio.hpp"

Player::Player(Scene* scene)
    : Spacecraft(scene)
{
    m_name = "player_ship";
    m_mesh.loadFromFile("data/meshes/player.obj");
}

void Player::ready()
{
    Spacecraft::ready(true);

    m_hud = m_scene->findObject("hud")->as<Hud>();
    m_hud->setMoney(0);

    Audio.playSound(_Audio::EFFECT_ENGINE);
    Audio.setVolume(_Audio::EFFECT_ENGINE, 0.1);

    auto tut = m_scene->findObject("tutorial")->as<Tutorial>();
    tut->show(TUTORIAL_OBJECTIVE);
}

void Player::exertHeat(float hdiff)
{
    m_heat = std::min(m_heat + hdiff, 100.f);

    if (m_heat >= 100.f)
        m_overheat = true;

    m_heatTimer = sf::seconds(0);
}

void Player::control()
{
    if (m_overheat)
    {
        Audio.setVolume(_Audio::EFFECT_ENGINE, 0.2);
        // Audio.stopSound(_Audio::EFFECT_ENGINE);
        return;
    }

    vec2 mov = Input.get()->getCursorPosition();
    m_aim = mov;

    m_body->rotateTowards(m_pos + m_aim, 200 * timer::delta);

    // Input.get()->rumble(Input.get()->getAcceleration() * 0.1, 20);

    float speed = Input.get()->getAcceleration() * 8.f;
    Audio.setVolume(_Audio::EFFECT_ENGINE, Input.get()->getAcceleration());

    if (speed > 0)
    {
        m_body->applyLinearImpulse(m_body->getDirection() * timer::delta * speed);
        exertHeat(speed * 2 * timer::delta);
    }
    else
    {
        Audio.setVolume(_Audio::EFFECT_ENGINE, 0.1);
        // Audio.stopSound(_Audio::EFFECT_ENGINE);
    }

    Renderer.setZoom(math::length(m_body->getLinearVelocity()));
}

void Player::shoot()
{
    if (m_overheat)
    {
        Audio.stopSound(_Audio::EFFECT_LASER);
        return;
    }

    if (Input.get()->isAction(Action::A_FIRE))
    {
        vec2 pos = m_body->getPosition();
        // vec2 dir = math::normalize(Renderer.getGlobalMousePosition() - pos);
        vec2 dir = math::normalize(m_aim);

        switch (m_weapon)
        {
            case Weapon::BASIC:
            {
                if (m_shootTimer < sf::milliseconds(100))
                    return;

                Renderer.shake(0.2f, 0.1f);
                Input.get()->rumble(0.2f, 100);

                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection(), BaseDamage, true);

                exertHeat(ShootHeatCost);
                Audio.playSound(_Audio::EFFECT_BLASTER);
                m_shootTimer = sf::seconds(0);
            }
            break;
            case Weapon::SHOTGUN:
            {
                if (m_shootTimer < sf::seconds(0.5))
                    return;

                Renderer.shake(0.5f, 0.1f);
                Input.get()->rumble(1.f, 100);

                vec2 side = vec2(dir.y, -dir.x) * 0.25f;

                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection(), ShotgunDamage, true);
                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() + side, ShotgunDamage, true);
                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() - side, ShotgunDamage, true);

                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() + (side * 0.25f), ShotgunDamage, true);
                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() - (side * 0.25f), ShotgunDamage, true);

                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() + (side * 0.5f), ShotgunDamage, true);
                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() - (side * 0.5f), ShotgunDamage, true);

                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() + (side * 0.75f), ShotgunDamage, true);
                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() - (side * 0.75f), ShotgunDamage, true);

                exertHeat(ShotgunHeatCost);
                Audio.playSound(_Audio::EFFECT_BLASTER);
                m_shootTimer = sf::seconds(0);
            }
            break;
            case Weapon::LASER:
            {
                RaycastCallback result;
                // m_scene->getPhysicsWorld()->castRay(&result, m_body->getPosition(), Renderer.getGlobalMousePosition());

                vec2 target = m_pos + m_aim;

                if (!isnan(target.x) and !isnan(target.y))
                {
                    m_scene->getPhysicsWorld()->castRay(&result, m_body->getPosition(), target);

                    Renderer.shake(0.2f, 0.1f);
                    Input.get()->rumble(0.2f, 100);

                    m_rayhit = {result.point.x, result.point.y};

                    if (m_shootTimer > sf::milliseconds(25) && result.hasHit)
                    {
                        if (result.object)
                        if (result.object->getName() == "drone")
                        {
                            auto drone = result.object->as<Drone>();
                            drone->damage(LaserDamage);
                        }

                        m_shootTimer = sf::seconds(0);
                    }

                    exertHeat(timer::delta * LaserHeatCost);
                    Audio.playSound(_Audio::EFFECT_LASER);
                }
            }
            break;
        }
    }
    else
    {
        Audio.stopSound(_Audio::EFFECT_LASER);
    }
}

void Player::update(float dt)
{
    m_heatTimer += sf::seconds(dt);
    m_shootTimer += sf::seconds(dt);

    control();
    shoot();

    if (Input.get()->isAction(Action::A_BASE_WEAPON))
        m_weapon = Weapon::BASIC;
    if (Input.get()->isAction(Action::A_SHOTGUN))
        m_weapon = Weapon::SHOTGUN;
    if (Input.get()->isAction(Action::A_LASER))
        m_weapon = Weapon::LASER;

    m_hud->setWeapon((int)m_weapon);

    if (m_heatTimer > sf::seconds(0.5))
    {
        m_heat = std::max(m_heat - timer::delta * HeatRegen, 0.f);

        if (m_heat == 0.f)
            m_overheat = false;
    }

    m_hud->setPlayerCoords(m_pos.x, m_pos.y);
    m_hud->setHeat(m_heat);
    m_hud->setHealthPercentage(float(m_health) / float(m_maxHealth));

    m_pos = m_body->getPosition();

    Spacecraft::update(dt);
}

void Player::draw()
{
    vec2 campos = m_pos + m_body->getLinearVelocity() * 0.2f;
    Renderer.setView(campos);

    if (m_weapon == Weapon::LASER && Input.get()->isAction(Action::A_FIRE))
    {
        Renderer.drawLineScaled(m_rayhit + vec2(1,0), m_rayhit + vec2(-1,0), sf::Color::Blue);
        Renderer.drawLineScaled(m_rayhit + vec2(0,1), m_rayhit + vec2(0,-1), sf::Color::Blue);

        Renderer.drawLineScaled(m_pos, m_pos + (m_aim), sf::Color::Red);
    }

    Renderer.drawLineScaled(m_pos + m_aim + vec2(1,0), m_pos + m_aim + vec2(-1,0), sf::Color::Blue);
    Renderer.drawLineScaled(m_pos + m_aim + vec2(0,1), m_pos + m_aim + vec2(0,-1), sf::Color::Blue);

    Spacecraft::draw();
}

void Player::onContact(SceneObject* other)
{
    if (!other) return;

    if (other->getName() == "enemy_bullet")
    {
        int dmg = other->as<Bullet>()->getDamage();
        m_health = std::max(0, m_health - dmg);

        auto tut = m_scene->findObject("tutorial")->as<Tutorial>();
        tut->show(TUTORIAL_HEALTH);
    }
}

void Player::addMoney(int value)
{
    m_money += value;

    m_hud->setMoney(m_money);
    m_health = std::min(m_maxHealth, m_health + 1);

    auto tut = m_scene->findObject("tutorial")->as<Tutorial>();
    tut->show(TUTORIAL_XP);
}