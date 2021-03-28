#include "Player.hpp"
#include "Scene/Scene.hpp"
#include "Audio/Audio.hpp"
#include "Physics/PhysicsWorld.hpp"
#include "Scene/Tutorial.hpp"
#include "Input/Input.hpp"
#include "Renderer.hpp"
#include "GameplayVars.hpp"
#include "Bullet.hpp"
#include "Drone.hpp"
#include "Hud.hpp"
#include "Objective.hpp"
#include "Rocket.hpp"
#include "Pulse.hpp"
#include "GameOver.hpp"
#include "Explosion.hpp"

Player::Player(Scene* scene)
    : Spacecraft(scene)
{
    m_name = "player_ship";

    std::vector<vec2> points(3);
    points[0] = {-1.f, 0.6};
    points[1] = {1., 0};
    points[2] = {-1.f, -0.6};

    m_body = m_scene->getPhysicsWorld()->addRigidBody({0,0}, true, points);

    m_mesh.loadFromFile("data/meshes/player.obj");
	m_arrow.loadFromFile("data/meshes/guide_arrow.obj");

	m_arrow.setOffset(vec2(0, -2));
	m_arrow.setScale(0.25);

    // m_health = 1;
}

void Player::ready()
{
    Spacecraft::ready(true);

	m_hud = m_scene->findObject<Hud>("hud");
    m_hud->setMoney(0);

    Audio.playSound(_Audio::EFFECT_ENGINE);
    Audio.setVolume(_Audio::EFFECT_ENGINE, 0.1);

    m_mesh.setScale(0.7f);
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
    if (m_overheat || isDead())
    {
        Audio.setVolume(_Audio::EFFECT_ENGINE, 0.2);
        // Audio.stopSound(_Audio::EFFECT_ENGINE);
		m_thruster.setVisible(false);
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
		thrust(m_body->getDirection() * timer::delta * speed);
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
    if (m_overheat || isDead())
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

                const float spread = 0.08f;

                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection(), ShotgunDamage, true);

                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() + (side * spread), ShotgunDamage, true);
                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() - (side * spread), ShotgunDamage, true);

                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() + (side * spread * 2.f), ShotgunDamage, true);
                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() - (side * spread * 2.f), ShotgunDamage, true);

                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() + (side * spread * 3.f), ShotgunDamage, true);
                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() - (side * spread * 3.f), ShotgunDamage, true);

                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() + (side * spread * 4.f), ShotgunDamage, true);
                m_scene->spawnObject<Bullet>(m_pos, m_body->getDirection() - (side * spread * 4.f), ShotgunDamage, true);

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
                        if (result.object->getName() == "drone" ||
							result.object->getName() == "merchant" ||
                            result.object->getName() == "gunner")
                        {
                            auto ship = result.object->as<Spacecraft>();
							ship->damage(LaserDamage);
                        }

                        m_shootTimer = sf::seconds(0);
                        m_scene->spawnObject<Explosion>(m_rayhit, sf::Color::Yellow);
                    }

                    exertHeat(timer::delta * LaserHeatCost);
                    Audio.playSound(_Audio::EFFECT_LASER);
                }
            }
            break;
            case Weapon::ROCKETS:
            {
                if (m_shootTimer < sf::seconds(0.5))
                    return;

                vec2 side = vec2(dir.y, -dir.x);

                m_scene->spawnObject<Rocket>(m_body->getPosition(), math::normalize(m_body->getDirection() + side * 0.25f));
                m_scene->spawnObject<Rocket>(m_body->getPosition(), math::normalize(m_body->getDirection() - side * 0.25f));
                m_scene->spawnObject<Rocket>(m_body->getPosition(), math::normalize(m_body->getDirection() + side));
                m_scene->spawnObject<Rocket>(m_body->getPosition(), math::normalize(m_body->getDirection() - side));

                m_scene->spawnObject<Rocket>(m_body->getPosition(), math::normalize(-m_body->getDirection() + side * 0.25f));
                m_scene->spawnObject<Rocket>(m_body->getPosition(), math::normalize(-m_body->getDirection() - side * 0.25f));
                m_scene->spawnObject<Rocket>(m_body->getPosition(), math::normalize(-m_body->getDirection() + side));
                m_scene->spawnObject<Rocket>(m_body->getPosition(), math::normalize(-m_body->getDirection() - side));

                exertHeat(RocketsCost);
                Audio.playSound(_Audio::EFFECT_ROCKET);
                m_shootTimer = sf::seconds(0);
            }
            break;
        }
    }
    else
    {
        Audio.stopSound(_Audio::EFFECT_LASER);
    }
}

void Player::switchWeapons()
{
    if (Input.get()->isAction(Action::A_BASE_WEAPON))
        m_weapon = Weapon::BASIC;
    if (Input.get()->isAction(Action::A_SHOTGUN) && gamevars::WeaponUnlocked[int(Weapon::SHOTGUN)])
        m_weapon = Weapon::SHOTGUN;
    if (Input.get()->isAction(Action::A_LASER) && gamevars::WeaponUnlocked[int(Weapon::LASER)])
        m_weapon = Weapon::LASER;
    if (Input.get()->isAction(Action::A_ROCKETS) && gamevars::WeaponUnlocked[int(Weapon::ROCKETS)])
        m_weapon = Weapon::ROCKETS;

    if (Input.get()->isAction(Action::A_BRAKE) &&
        gamevars::BrakeUnlocked &&
        m_shootTimer > sf::seconds(0.5) &&
        !m_overheat)
    {
        m_body->fullStop();

        m_scene->spawnObject<Pulse>(m_pos);

        exertHeat(33);
        m_shootTimer = sf::seconds(0);
    }

    m_hud->setWeapon((int)m_weapon);
}

void Player::update(float dt)
{
    m_heatTimer += sf::seconds(dt);
    m_shootTimer += sf::seconds(dt);

    if (m_pos.x > 700.f || m_pos.x < -700.f || m_pos.y < -700.f || m_pos.y > 700.f)
    {
        m_body->rotateTowards(vec2(0,0), 200 * timer::delta);
        thrust(m_body->getDirection() * timer::delta * 10.f);
        m_hud->setShowOutOfBounds(true);
    }
    else
    {
        control();
        shoot();
        switchWeapons();

        m_hud->setShowOutOfBounds(false);
    }

    if (m_heatTimer > sf::seconds(0.5))
    {
        m_heat = std::max(m_heat - timer::delta * HeatRegen, 0.f);

        if (m_heat == 0.f)
            m_overheat = false;
    }

    m_hud->setHeat(m_heat);
    m_hud->setHealthPercentage(float(m_health) / float(m_maxHealth));

    m_pos = m_body->getPosition();

	vec2 towards = m_scene->findObject<Objective>("objective")->getPosition() - m_pos;
	towards = math::normalize(towards);

	m_arrow.setRotation(atan2(towards.x, -towards.y));
	m_arrow.setPosition(m_pos);

    Spacecraft::update(dt);
}

void Player::draw()
{
    vec2 campos = m_pos + m_body->getLinearVelocity() * 0.2f;
    Renderer.setView(campos);

    if (m_weapon == Weapon::LASER && Input.get()->isAction(Action::A_FIRE))
    {
        // Renderer.drawLineScaled(m_rayhit + vec2(1,0), m_rayhit + vec2(-1,0), sf::Color::Blue);
        // Renderer.drawLineScaled(m_rayhit + vec2(0,1), m_rayhit + vec2(0,-1), sf::Color::Blue);

        Renderer.drawLineScaled(m_pos, m_pos + (m_aim), sf::Color::Red);
    }

    Renderer.drawLineScaled(m_pos + m_aim + vec2(0.2,0), m_pos + m_aim + vec2(1,0), sf::Color::White);
    Renderer.drawLineScaled(m_pos + m_aim + vec2(-0.2,0), m_pos + m_aim + vec2(-1,0), sf::Color::White);
    Renderer.drawLineScaled(m_pos + m_aim + vec2(0,0.2), m_pos + m_aim + vec2(0,1), sf::Color::White);
    Renderer.drawLineScaled(m_pos + m_aim + vec2(0,-0.2), m_pos + m_aim + vec2(0,-1), sf::Color::White);

    Spacecraft::draw();

	m_arrow.draw();
}

void Player::heal()
{
    m_health = m_maxHealth;
}

void Player::onContact(SceneObject* other)
{
    if (!other) return;

    if (other->getName() == "enemy_bullet")
    {
        int dmg = other->as<Bullet>()->getDamage();
        m_health = std::max(0, m_health - dmg);

        if (m_health == 0)
            m_scene->findObject<GameOver>("game_over")->show();

		auto tut = m_scene->findObject<Tutorial>("tutorial");
        tut->show(TUTORIAL_HEALTH);
    }
}

void Player::addMoney(int value)
{
	gamevars::PlayerMoney += value;
    //m_money += value;

    m_hud->setMoney(gamevars::PlayerMoney);
    m_health = std::min(m_maxHealth, m_health + 1);

	auto tut = m_scene->findObject<Tutorial>("tutorial");
    tut->show(TUTORIAL_XP);
}

bool Player::isDead() const
{
    return m_health == 0;
}