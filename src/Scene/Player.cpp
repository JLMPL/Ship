#include "Player.hpp"
#include "Physics/PhysicsWorld.hpp"
#include "Renderer.hpp"
#include "Layers/HudLayer.hpp"

static constexpr float HeatRegen = 35.f;

Player::Player(PhysicsWorld* pWorld)
    : m_pWorld(pWorld)
{
    m_body = pWorld->addRigidBody({0,0});
    auto bd = pWorld->addRigidBody({-2,-2});
}

void Player::control(float dt)
{
    if (m_overheat) return;

    auto rb = m_body->body;
    sf::Vector2f bodyPos = {rb->GetPosition().x, rb->GetPosition().y};

    sf::Vector2f mp = Renderer::Get().getGlobalMousePosition();
    sf::Vector2f mous = {mp.x - bodyPos.x, mp.y - bodyPos.y};
    mous = math::normalize(mous);

    float bodyAngle = rb->GetAngle();
    sf::Vector2f bodyVec = {cos(bodyAngle), sin(bodyAngle)};

    float dot = acos(bodyVec.x*mous.x+bodyVec.y*mous.y);

    float acc = dt * 50 * dot;

    if (math::cross(mous, bodyVec) > 0)
        acc = -acc;
    else if (math::cross(mous, bodyVec) == 0)
        acc = 0;

    if (abs(acc) > 0.0005f)
        rb->ApplyTorque(acc, true);

    vec2 dir = {0,0};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        dir.y += -1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        dir.y += 1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        dir.x += -1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        dir.x += 1.f;

    float speed = (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) ? 5.f : 2.f;

    if (dir.x != 0.f or dir.y != 0.f)
    {
        dir = math::normalize(dir);
        rb->ApplyLinearImpulseToCenter({dir.x * dt * 2.f, dir.y * dt * speed}, true);
        exertHeat(10.f * dt);
    }
}

void Player::shoot()
{
    if (m_overheat) return;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_shootTimer.getElapsedTime().asMilliseconds() > 250)
    {
        auto bod = m_body->body->GetPosition();
        vec2 pos = {bod.x, bod.y};

        vec2 dir = math::normalize(Renderer::Get().getGlobalMousePosition() - pos);

        m_pWorld->spawnBullet({pos.x, pos.y}, dir);
        exertHeat(5.f);
        m_shootTimer.restart();
    }
}

void Player::update(float dt)
{
    control(dt);
    shoot();

    if (m_heatTimer.getElapsedTime() > sf::seconds(0.5))
    {
        m_heat = std::max(m_heat - dt * HeatRegen, 0.f);

        if (m_heat == 0.f)
            m_overheat = false;
    }

    sf::Vector2f bodyPos = {m_body->body->GetPosition().x, m_body->body->GetPosition().y};
    Renderer::Get().setView(bodyPos);

    HudLayer::setHeat(m_heat);
}

void Player::draw()
{
    auto rb = m_body->body;

    auto bodyPos = rb->GetPosition();
    float bodyAngle = rb->GetAngle();
/*    Renderer::Get().drawLineScaled(
        sf::Vector2f(bodyPos.x, bodyPos.y),
        sf::Vector2f(bodyPos.x + cos(bodyAngle) * 2, bodyPos.y + sin(bodyAngle) * 2),
        sf::Color::Green);

    Renderer::Get().drawLineScaled({bodyPos.x, bodyPos.y}, Renderer::Get().getGlobalMousePosition(), sf::Color::Red);
*/
    RaycastCallback rc;
    m_pWorld->castRay(&rc, {bodyPos.x, bodyPos.y}, Renderer::Get().getGlobalMousePosition());

    if (rc.m_hasHit)
    {
        Renderer::Get().drawLineScaled(rc.m_point, rc.m_point + rc.m_normal, sf::Color::Blue);
    }
}

void Player::exertHeat(float heat)
{
    m_heat = std::min(m_heat + heat, 100.f);
    if (m_heat >= 100.f)
    {
        m_overheat = true;
    }
    m_heatTimer.restart();
}
