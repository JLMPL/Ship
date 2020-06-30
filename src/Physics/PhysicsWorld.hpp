#pragma once
#include "DebugDrawer.hpp"
#include "RigidBody.hpp"
#include "StaticBody.hpp"
#include "RaycastCallback.hpp"
#include "ContactListener.hpp"
#include "Core/Math.hpp"
#include <vector>

class PhysicsWorld
{
public:
    PhysicsWorld();
    ~PhysicsWorld();

    void update(float dt);
    void draw();

    RigidBody* addRigidBody(const vec2& pos, bool player);
    StaticBody* addStaticBody(const vec2& pos, float radius);
    RigidBody* spawnBullet(const vec2& origin, const vec2& dir, bool player);
    void castRay(b2RayCastCallback* callback, const sf::Vector2f& from, const sf::Vector2f& to);

private:
    b2World m_pWorld;
    // std::vector<RigidBody::Ptr> m_bodies;

    DebugDrawer m_pDrawer;
    ContactListener m_contactListener;
};