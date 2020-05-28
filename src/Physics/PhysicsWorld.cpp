#include "PhysicsWorld.hpp"
#include "Core/Math.hpp"
#include <SFML/Graphics.hpp>

#include "Renderer.hpp"

enum CollisionGroup
{
    CelestialBodies = 1 << 0,
    Ships = 1 << 1,
    Bullets = 1 << 2
};

PhysicsWorld::PhysicsWorld()
    : m_pWorld({0.f, 0.f})
{
    m_pDrawer.SetFlags(b2Draw::e_shapeBit);
    m_pWorld.SetDebugDraw(&m_pDrawer);
    m_pWorld.SetContactListener(&m_contactListener);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(10.0f, 10.0f);
    m_groundBody = m_pWorld.CreateBody(&groundBodyDef);

    b2CircleShape groundShape;
    groundShape.m_p.Set(0.f, 0.f);
    groundShape.m_radius = 2.f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundShape;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.3f;
    fixtureDef.filter.categoryBits = CollisionGroup::CelestialBodies;
    fixtureDef.filter.maskBits = CollisionGroup::Ships | CollisionGroup::Bullets;

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

    verts[0] = {-1.f, 0.6};
    verts[1] = {1., 0};
    verts[2] = {-1.f, -0.6};

    b2PolygonShape shape;
    shape.Set(verts, 3);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.5f;
    fixtureDef.friction = 0.3f;
    fixtureDef.filter.categoryBits = CollisionGroup::Ships;
    fixtureDef.filter.maskBits = CollisionGroup::Ships | CollisionGroup::CelestialBodies | CollisionGroup::Bullets;

    body->CreateFixture(&fixtureDef);
    body->SetAngularDamping(5.f);

    m_bodies.emplace_back(new RigidBody(body, &m_pWorld));

    return m_bodies.back().get();
}

RigidBody* PhysicsWorld::spawnBullet(const vec2& origin, const vec2& dir)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(origin.x, origin.y);

    b2Body* body = m_pWorld.CreateBody(&bodyDef);

    b2Vec2 verts[4];

    verts[0] = {0.1f, 0.f};
    verts[1] = {-0.1f, 0.f};
    verts[2] = {0.f, 0.1f};
    verts[3] = {0.f, -0.1f};

    b2CircleShape shape;
    shape.m_p.Set(0,0);
    shape.m_radius = 0.1f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.02f;
    fixtureDef.friction = 0.3f;
    fixtureDef.filter.categoryBits = CollisionGroup::Bullets;
    fixtureDef.filter.maskBits = CollisionGroup::CelestialBodies | CollisionGroup::Ships;

    body->CreateFixture(&fixtureDef);
    body->SetBullet(true);
    body->ApplyLinearImpulseToCenter({dir.x, dir.y}, true);
    body->SetTransform(body->GetPosition(), atan2(dir.x, dir.y));

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
