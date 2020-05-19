#pragma once
#include "DebugDrawer.hpp"

class PhysicsWorld
{
public:
    PhysicsWorld();
    ~PhysicsWorld() = default;

    void update(float dt);
    void draw();

private:
    b2World m_pWorld;
    b2Body* m_groundBody = nullptr;
    b2Body* m_body = nullptr;
    b2Body* m_body2 = nullptr;

    DebugDrawer m_pDrawer;

    float m_frameTimer = 0.f;
};