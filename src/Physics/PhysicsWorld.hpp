#pragma once
#include "DebugDrawer.hpp"
#include "RigidBody.hpp"
#include "RaycastCallback.hpp"
#include "Core/Math.hpp"
#include <vector>

class PhysicsWorld
{
public:
    PhysicsWorld();
    ~PhysicsWorld();

    void update(float dt);
    void draw();

    RigidBody* addRigidBody(const sf::Vector2f& pos);
    void castRay(b2RayCastCallback* callback, const sf::Vector2f& from, const sf::Vector2f& to);

private:
    b2World m_pWorld;

    b2Body* m_groundBody = nullptr;
    std::vector<RigidBody::Ptr> m_bodies;

    DebugDrawer m_pDrawer;
};