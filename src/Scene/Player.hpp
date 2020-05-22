#pragma once
#include "Physics/RigidBody.hpp"

class PhysicsWorld;

class Player
{
public:
    Player(PhysicsWorld* pWorld);

    void update(float dt);
    void draw();

private:
    PhysicsWorld* m_pWorld = nullptr;
    RigidBody* m_body = nullptr;
};