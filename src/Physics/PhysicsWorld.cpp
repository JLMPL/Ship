#include "PhysicsWorld.hpp"
#include "Core/Math.hpp"
#include <SFML/Graphics.hpp>

#include "Renderer.hpp"

PhysicsWorld::PhysicsWorld()
    : m_pWorld({0.f, 0.f})
{
    m_pDrawer.SetFlags(b2Draw::e_shapeBit);
    m_pWorld.SetDebugDraw(&m_pDrawer);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(10.0f, 10.0f);
    m_groundBody = m_pWorld.CreateBody(&groundBodyDef);

    b2CircleShape groundShape;
    groundShape.m_p.Set(0.f, 0.f);
    groundShape.m_radius = 1.f;
    m_groundBody->CreateFixture(&groundShape, 0.1f);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(4.0f, 4.0f);
    m_body = m_pWorld.CreateBody(&bodyDef);
    m_body->SetAngularDamping(5.f);

    b2Vec2 verts[3];

    verts[0] = {-0.5f, 0.3};
    verts[1] = {0.5, 0};
    verts[2] = {-0.5f, -0.3};

    b2PolygonShape dynashap;
    dynashap.Set(verts, 3);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynashap;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    m_body->CreateFixture(&fixtureDef);

    bodyDef.position.Set(6.f, 6.f);
    m_body2 = m_pWorld.CreateBody(&bodyDef);
    m_body2->CreateFixture(&fixtureDef);
}

void PhysicsWorld::update(float dt)
{
    sf::Vector2f bodyPos = {m_body->GetPosition().x, m_body->GetPosition().y};

    sf::Vector2f mp = Renderer::Get().getGlobalMousePosition();
    sf::Vector2f mous = {mp.x - bodyPos.x, mp.y - bodyPos.y};
    mous = math::normalize(mous);

    float bodyAngle = m_body->GetAngle();
    sf::Vector2f bodyVec = {cos(bodyAngle), sin(bodyAngle)};

    float dot = acos(bodyVec.x*mous.x+bodyVec.y*mous.y);

    float acc = dt * 10 * dot;

    if (math::cross(mous, bodyVec) > 0)
        acc = -acc;
    else if (math::cross(mous, bodyVec) == 0)
        acc = 0;

    if (abs(acc) > 0.0005f)
        m_body->ApplyTorque(acc, true);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        m_body->ApplyLinearImpulseToCenter({0,-2.5f * dt}, true);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        m_body->ApplyLinearImpulseToCenter({0,2.5f * dt}, true);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        m_body->ApplyLinearImpulseToCenter({-2.5f * dt,0}, true);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        m_body->ApplyLinearImpulseToCenter({2.5f * dt,0}, true);

    m_pWorld.Step(dt, 6, 2);
    Renderer::Get().setView(bodyPos);
}

void PhysicsWorld::draw()
{
    m_pWorld.DebugDraw();

    auto bodyPos = m_body->GetPosition();
    float bodyAngle = m_body->GetAngle();
    Renderer::Get().drawLineScaled(
        sf::Vector2f(bodyPos.x, bodyPos.y),
        sf::Vector2f(bodyPos.x + cos(bodyAngle) * 2, bodyPos.y + sin(bodyAngle) * 2),
        sf::Color::Green);

    Renderer::Get().drawLineScaled({bodyPos.x, bodyPos.y}, Renderer::Get().getGlobalMousePosition(), sf::Color::Red);
}
