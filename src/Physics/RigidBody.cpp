#include "RigidBody.hpp"

RigidBody::RigidBody(b2Body* bd, b2World* world)
    : m_body(bd), m_world(world)
{
}

RigidBody::~RigidBody()
{
    m_world->DestroyBody(m_body);
}

void RigidBody::applyTorque(float torq)
{
    m_body->ApplyTorque(torq, true);
}

void RigidBody::applyLinearImpulse(const vec2& impulse)
{
    m_body->ApplyLinearImpulseToCenter({impulse.x, impulse.y}, true);
}

vec2 RigidBody::getPosition() const
{
    auto pos = m_body->GetPosition();
    return {pos.x, pos.y};
}

vec2 RigidBody::getDirection() const
{
    float angle = getAngle();
    return {cos(angle), sin(angle)};
}

float RigidBody::getAngle() const
{
    return m_body->GetAngle();
}
