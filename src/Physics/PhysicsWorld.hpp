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
    ~PhysicsWorld() = default;

    void update(float dt);
    void draw();

    RigidBody::Ref addRigidBody(const vec2& pos, bool player, const std::vector<vec2>& points, bool superSpecialDamping = false);
    RigidBody::Ref spawnBullet(const vec2& origin, const vec2& dir, bool player);
    StaticBody::Ref addStaticBody(const vec2& pos, float radius);
    void castRay(b2RayCastCallback* callback, const sf::Vector2f& from, const sf::Vector2f& to);

private:
    b2World m_pWorld;
    std::vector<RigidBody::Ref> m_rigidBodies;
    std::vector<StaticBody::Ref> m_staticBodies;

    DebugDrawer m_pDrawer;
    ContactListener m_contactListener;

};