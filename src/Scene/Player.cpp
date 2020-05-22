#include "Player.hpp"
#include "Physics/PhysicsWorld.hpp"
#include "Renderer.hpp"
#include "Layers/HudLayer.hpp"

Player::Player(PhysicsWorld* pWorld)
    : m_pWorld(pWorld)
{
    m_body = pWorld->addRigidBody({0,0});
    auto bd = pWorld->addRigidBody({-2,-2});
}

void Player::control(float dt)
{
    auto rb = m_body->body;
    sf::Vector2f bodyPos = {rb->GetPosition().x, rb->GetPosition().y};

    sf::Vector2f mp = Renderer::Get().getGlobalMousePosition();
    sf::Vector2f mous = {mp.x - bodyPos.x, mp.y - bodyPos.y};
    mous = math::normalize(mous);

    float bodyAngle = rb->GetAngle();
    sf::Vector2f bodyVec = {cos(bodyAngle), sin(bodyAngle)};

    float dot = acos(bodyVec.x*mous.x+bodyVec.y*mous.y);

    float acc = dt * 10 * dot;

    if (math::cross(mous, bodyVec) > 0)
        acc = -acc;
    else if (math::cross(mous, bodyVec) == 0)
        acc = 0;

    if (abs(acc) > 0.0005f)
        rb->ApplyTorque(acc, true);

    vec2 dir = {0,0};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        dir.y += -2.5f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        dir.y += 2.5f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        dir.x += -2.5f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        dir.x += 2.5f;
    }

    if (dir.x != 0 or dir.y != 0)
    {
        rb->ApplyLinearImpulseToCenter({dir.x * dt, dir.y * dt}, true);
        m_heat += dt * 15.f;
    }

    Renderer::Get().setView(bodyPos);
}

void Player::update(float dt)
{
    control(dt);

    m_heat = std::max(m_heat - dt * 5.f, 0.f);

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
