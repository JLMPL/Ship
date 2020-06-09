#include "RigidBody.hpp"

RigidBody::RigidBody(b2Body* bd, b2World* world, Type type)
    : m_body(bd), m_world(world), m_type(type)
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

void RigidBody::setUserData(int* id)
{
    m_body->SetUserData((void*)id);
}

int RigidBody::getUserData() const
{
    return *((int*)m_body->GetUserData());
}

const RigidBody::Type& RigidBody::getType() const
{
    return m_type;
}