#include "PhysicsWorld.hpp"
#include "Core/Math.hpp"
#include "Renderer.hpp"

enum CollisionGroup
{
    CelestialBodies = 1 << 0,
    PlayerShip      = 1 << 1,
    EnemyShip       = 1 << 2,
    PlayerBullets   = 1 << 3,
    EnemyBullets    = 1 << 4
};

PhysicsWorld::PhysicsWorld()
    : m_pWorld({0.f, 0.f})
{
    m_pDrawer.SetFlags(b2Draw::e_shapeBit);
    m_pWorld.SetDebugDraw(&m_pDrawer);
    m_pWorld.SetContactListener(&m_contactListener);
}

RigidBody::Ref PhysicsWorld::addRigidBody(const sf::Vector2f& pos, bool player, const std::vector<vec2>& points)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x, pos.y);

    b2Body* body = m_pWorld.CreateBody(&bodyDef);

    std::vector<b2Vec2> verts(points.size());

    for (int i = 0; i < verts.size(); i++)
    {
        verts[i].x = points[i].x;
        verts[i].y = points[i].y;
    }

    // b2Vec2 verts[3];

    // verts[0] = {-1.f, 0.6};
    // verts[1] = {1., 0};
    // verts[2] = {-1.f, -0.6};

    // b2PolygonShape shape;
    // shape.Set(verts, 3);

    b2PolygonShape shape;
    shape.Set(verts.data(), verts.size());

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.5f;
    fixtureDef.friction = 0.3f;

    if (player)
    {
        fixtureDef.filter.categoryBits = CollisionGroup::PlayerShip;
        fixtureDef.filter.maskBits = CollisionGroup::EnemyShip | CollisionGroup::CelestialBodies | CollisionGroup::EnemyBullets;
    }
    else
    {
        fixtureDef.filter.categoryBits = CollisionGroup::EnemyShip;
        fixtureDef.filter.maskBits = CollisionGroup::PlayerShip | CollisionGroup::CelestialBodies | CollisionGroup::PlayerBullets | CollisionGroup::EnemyShip;
    }

    body->CreateFixture(&fixtureDef);
    body->SetAngularDamping(5.f);

    m_rigidBodies.emplace_back(new RigidBody(body, &m_pWorld, player ? RigidBody::PlayerShip : RigidBody::EnemyShip));

    return m_rigidBodies.back();
}

StaticBody::Ref PhysicsWorld::addStaticBody(const vec2& pos, float radius)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(pos.x, pos.y);
    auto body = m_pWorld.CreateBody(&bodyDef);

    b2CircleShape groundShape;
    groundShape.m_p.Set(0.f, 0.f);
    groundShape.m_radius = radius;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundShape;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 0.3f;
    fixtureDef.filter.categoryBits = CollisionGroup::CelestialBodies;
    fixtureDef.filter.maskBits =
        CollisionGroup::PlayerShip |
        CollisionGroup::EnemyShip |
        CollisionGroup::PlayerBullets |
        CollisionGroup::EnemyBullets;

    body->CreateFixture(&groundShape, 0.1f);

    m_staticBodies.emplace_back(new StaticBody(body, &m_pWorld));
    return m_staticBodies.back();
}

RigidBody::Ref PhysicsWorld::spawnBullet(const vec2& origin, const vec2& dir, bool player)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(origin.x, origin.y);

    b2Body* body = m_pWorld.CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_p.Set(0,0);
    shape.m_radius = 0.1f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.02f;
    fixtureDef.friction = 0.3f;

    if (player)
    {
        fixtureDef.filter.categoryBits = CollisionGroup::PlayerBullets;
        fixtureDef.filter.maskBits = CollisionGroup::CelestialBodies | CollisionGroup::EnemyShip;
    }
    else
    {
        fixtureDef.filter.categoryBits = CollisionGroup::EnemyBullets;
        fixtureDef.filter.maskBits = CollisionGroup::CelestialBodies | CollisionGroup::PlayerShip;
    }

    body->CreateFixture(&fixtureDef);
    body->SetBullet(true);
    body->ApplyLinearImpulseToCenter({dir.x, dir.y}, true);
    body->SetTransform(body->GetPosition(), atan2(dir.x, dir.y));

    m_rigidBodies.emplace_back(new RigidBody(body, &m_pWorld, player ? RigidBody::PlayerBullet : RigidBody::EnemyBullet));
    return m_rigidBodies.back();
}

void PhysicsWorld::castRay(b2RayCastCallback* callback, const sf::Vector2f& from, const sf::Vector2f& to)
{
    m_pWorld.RayCast(callback, {from.x, from.y}, {to.x, to.y});
}

void PhysicsWorld::update(float dt)
{
    for (auto i = m_rigidBodies.begin(); i != m_rigidBodies.end();)
    {
        if (i->use_count() == 1)
            i = m_rigidBodies.erase(i);
        else
            i++;
    }

    for (auto i = m_staticBodies.begin(); i != m_staticBodies.end();)
    {
        if (i->use_count() == 1)
            i = m_staticBodies.erase(i);
        else
            i++;
    }

    m_pWorld.Step(dt, 6, 2);
}

void PhysicsWorld::draw()
{
    m_pWorld.DebugDraw();
}

