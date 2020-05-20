#include "PhysicsWorld.hpp"
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
    m_body->SetAngularDamping(10.f);

    // b2PolygonShape m_dynamicBox;
    // m_dynamicBox.SetAsBox(0.5f, 0.5f);

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

float length(const sf::Vector2f& v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

sf::Vector2f normalize(const sf::Vector2f& v)
{
    float len = length(v);
    return sf::Vector2f(
        v.x / len,
        v.y / len
    );
}

float cross(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return (a.x*b.y) - (a.y*b.x);
}

void PhysicsWorld::update(float dt)
{
    sf::Vector2f bodyPos = {m_body->GetPosition().x, m_body->GetPosition().y};
    sf::Vector2f mous = {(sf::Mouse::getPosition().x / 32) - bodyPos.x, (sf::Mouse::getPosition().y / 32) - bodyPos.y};
    mous = normalize(mous);

    float bodyAngle = m_body->GetAngle();
    sf::Vector2f bodyVec = {cos(bodyAngle), sin(bodyAngle)};

    float dot = acos(bodyVec.x*mous.x+bodyVec.y*mous.y);

    float acc = dt * 10 * dot;

    if (cross(mous, bodyVec) > 0)
        acc = -acc;
    else if (cross(mous, bodyVec) < 0)
    {
    }
    else
        acc = 0;

    m_body->ApplyTorque(acc, true);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        m_body->ApplyLinearImpulseToCenter({0,-5.f * dt}, true);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        m_body->ApplyLinearImpulseToCenter({0,5.f * dt}, true);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_body->ApplyLinearImpulseToCenter({-5.f * dt,0}, true);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_body->ApplyLinearImpulseToCenter({5.f * dt,0}, true);

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

    auto bodyPos = m_body->GetPosition();
    bodyPos.x *= 32.f;
    bodyPos.y *= 32.f;
    auto mous = sf::Mouse::getPosition();
    Renderer::Get().drawLine(sf::Vector2f(bodyPos.x, bodyPos.y), sf::Vector2f(mous.x, mous.y), sf::Color::White);

    float bodyAngle = m_body->GetAngle();
    Renderer::Get().drawLine(
        sf::Vector2f(bodyPos.x, bodyPos.y),
        sf::Vector2f(bodyPos.x + cos(bodyAngle) * 100, bodyPos.y + sin(bodyAngle) * 100),
        sf::Color::Green);
}
