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
}

PhysicsWorld::~PhysicsWorld()
{
    m_pWorld.DestroyBody(m_groundBody);
}

RigidBody* PhysicsWorld::addRigidBody(const sf::Vector2f& pos)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x, pos.y);

    b2Body* body = m_pWorld.CreateBody(&bodyDef);

    b2Vec2 verts[3];

    verts[0] = {-0.5f, 0.3};
    verts[1] = {0.5, 0};
    verts[2] = {-0.5f, -0.3};

    b2PolygonShape shape;
    shape.Set(verts, 3);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
    body->SetAngularDamping(5.f);

    m_bodies.emplace_back(new RigidBody(body, &m_pWorld));

    return m_bodies.back().get();
}

void PhysicsWorld::castRay(b2RayCastCallback* callback, const sf::Vector2f& from, const sf::Vector2f& to)
{
    m_pWorld.RayCast(callback, {from.x, from.y}, {to.x, to.y});
}

void PhysicsWorld::update(float dt)
{
    m_pWorld.Step(dt, 6, 2);
}

void PhysicsWorld::draw()
{
    m_pWorld.DebugDraw();
}
