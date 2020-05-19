#include "PhysicsWorld.hpp"
#include <SFML/Graphics.hpp>

PhysicsWorld::PhysicsWorld()
    : m_pWorld({0.f, 0.f})
{
    m_pDrawer.SetFlags(b2Draw::e_shapeBit);
    m_pWorld.SetDebugDraw(&m_pDrawer);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(10.0f, 10.0f);
    m_groundBody = m_pWorld.CreateBody(&groundBodyDef);

    b2CircleShape groundShape;
    groundShape.m_p.Set(10.f, 10.f);
    groundShape.m_radius = 1.f;
    m_groundBody->CreateFixture(&groundShape, 0.1f);


    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(4.0f, 4.0f);
    m_body = m_pWorld.CreateBody(&bodyDef);
    m_body->SetAngularDamping(10.f);

    // b2PolygonShape m_dynamicBox;
    // m_dynamicBox.SetAsBox(0.5f, 0.5f);

    b2CircleShape dynashap;
    dynashap.m_p.Set(0.f, 0.f);
    dynashap.m_radius = 0.5f;

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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_body->ApplyLinearImpulseToCenter({0,-5.f * dt}, true);
        m_body->ApplyTorque(0.f, true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_body->ApplyLinearImpulseToCenter({0,5.f * dt}, true);
        m_body->ApplyTorque(0.f, true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_body->ApplyLinearImpulseToCenter({-5.f * dt,0}, true);
        m_body->ApplyTorque(0.f, true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_body->ApplyLinearImpulseToCenter({5.f * dt,0}, true);
        m_body->ApplyTorque(0.f, true);
    }

    m_frameTimer += dt;
    if (m_frameTimer > 1.f/60.f)
    {
        m_pWorld.Step(1.f/60.f, 6, 2);
        m_frameTimer = 0.f;
    }
}

void PhysicsWorld::draw()
{
    m_pWorld.DebugDraw();
}
