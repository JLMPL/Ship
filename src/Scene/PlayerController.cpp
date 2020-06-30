#include "PlayerController.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"
#include "Layers/HudLayer.hpp"
#include "Events/EventQueue.hpp"

static constexpr float HeatRegen = 100.f;
static constexpr float MoveHeatCost = 8.f;
static constexpr float ShootHeatCost = 4.f;

PlayerController::PlayerController(Scene* scene, int id) : Controller(scene, id)
{
    m_body = m_scene->addRigidBody(m_id, RigidBody::PlayerShip);
    m_tr = m_scene->getTransform(0);
    m_health = m_scene->addHealth(m_id, 100, 100);
}

void PlayerController::control(float dt)
{
    if (m_overheat) return;
    if (!m_body) return;

    m_body->rotateTowards(Renderer::get().getGlobalMousePosition(), 100 * dt);

    vec2 dir = {0,0};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        dir.y += -1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        dir.y += 1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        dir.x += -1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        dir.x += 1.f;

    float speed = (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) ? 8.f : 2.f;

    if (dir.x != 0.f or dir.y != 0.f)
    {
        dir = math::normalize(dir);
        m_body->applyLinearImpulse(dir * dt * speed);
        exertHeat(MoveHeatCost * dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        m_body->fullStop();
    }

    Renderer::get().setZoom(math::length(m_body->getLinearVelocity()));
}

void PlayerController::shoot()
{
    if (m_overheat) return;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_shootTimer.getElapsedTime().asMilliseconds() > 250)
    {
        vec2 pos = m_body->getPosition();
        vec2 dir = math::normalize(Renderer::get().getGlobalMousePosition() - pos);

        int bullet = m_scene->createEntity({pos.x, pos.y});
        m_scene->addRigidBody(bullet, RigidBody::PlayerBullet, pos, dir);

        EventQueue::get().registerCallback(Event::DamageEntity, bullet,
        [=](const Event& event, int ent)
        {
            m_scene->destroyEntity(bullet);
        });

        exertHeat(ShootHeatCost);
        m_shootTimer.restart();
    }
}

void PlayerController::exertHeat(float heat)
{
    m_heat = std::min(m_heat + heat, 100.f);
    if (m_heat >= 100.f)
    {
        m_overheat = true;
    }
    m_heatTimer.restart();
}

void PlayerController::update(float dt)
{
    control(dt);
    shoot();

    if (m_heatTimer.getElapsedTime() > sf::seconds(0.5))
    {
        m_heat = std::max(m_heat - dt * HeatRegen, 0.f);

        if (m_heat == 0.f)
            m_overheat = false;
    }

    m_tr->pos = m_body->getPosition();
    Renderer::get().setView(m_tr->pos);

    HudLayer::setHeat(m_heat);
    HudLayer::setHealthPercentage(float(m_health->hp) / float(m_health->maxHp));
}
