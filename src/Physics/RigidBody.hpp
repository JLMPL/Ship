#pragma once
#include "Libs/box2d/box2d.h"
#include <memory>

class RigidBody
{
public:
    using Ptr = std::unique_ptr<RigidBody>;

    RigidBody(b2Body* bd, b2World* world);
    ~RigidBody();

public:
    b2Body* body = nullptr;

private:
    b2World* m_world = nullptr;
};