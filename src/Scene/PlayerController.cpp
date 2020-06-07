#include "PlayerController.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"
#include "Layers/HudLayer.hpp"

static constexpr float HeatRegen = 100.f;


PlayerController::PlayerController(Scene* scene, int id) : Controller(scene, id)
{
    m_body = m_scene->addRigidBody(m_id, true);
}

void PlayerController::control(float dt)
{
    if (m_overheat) return;
    if (!m_body) return;

    sf::Vector2f bodyPos = m_body->getPosition();

    sf::Vector2f mp = Renderer::get().getGlobalMousePosition();
    sf::Vector2f mous = mp - bodyPos;
    mous = math::normalize(mous);

    sf::Vector2f bodyVec = m_body->getDirection();
    float dot = acos(math::dot(bodyVec, mous));

    float acc = dt * 50 * dot;

    if (math::cross(mous, bodyVec) > 0)
        acc = -acc;
    else if (math::cross(mous, bodyVec) == 0)
        acc = 0;

    if (abs(acc) > 0.0005f)
        m_body->applyTorque(acc);

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
        exertHeat(10.f * dt);
    }
}

void PlayerController::shoot()
{
    if (m_overheat) return;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_shootTimer.getElapsedTime().asMilliseconds() > 250)
    {
        vec2 pos = m_body->getPosition();

        vec2 dir = math::normalize(Renderer::get().getGlobalMousePosition() - pos);

        // m_pWorld->spawnBullet({pos.x, pos.y}, dir, true);
        exertHeat(5.f);
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

    Renderer::get().setView(m_body->getPosition());

    HudLayer::setHeat(m_heat);
}
