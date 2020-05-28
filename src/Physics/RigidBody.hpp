#pragma once
#include "Libs/box2d/box2d.h"
#include "Core/Math.hpp"
#include <memory>

class RigidBody
{
public:
    using Ptr = std::unique_ptr<RigidBody>;

    RigidBody(b2Body* bd, b2World* world);
    ~RigidBody();

    void applyTorque(float torq);
    void applyLinearImpulse(const vec2& impulse);

    vec2 getPosition() const;
    vec2 getDirection() const;
    float getAngle() const;

private:
    b2Body* m_body = nullptr;
    b2World* m_world = nullptr;
};