#include "RigidBody.hpp"

RigidBody::RigidBody(b2Body* bd, b2World* world, Type type)
    : m_body(bd), m_world(world), m_type(type)
{
    setUserData(NULL);
}

RigidBody::~RigidBody()
{
    m_world->DestroyBody(m_body);
}

void RigidBody::rotateTowards(const vec2& target, float speed)
{
    sf::Vector2f dir = target - getPosition();
    dir = math::normalize(dir);

    sf::Vector2f bodyVec = getDirection();
    float dot = acos(math::dot(bodyVec, dir));

    float acc = speed * dot;

    if (math::cross(dir, bodyVec) > 0)
        acc = -acc;
    else if (math::cross(dir, bodyVec) == 0)
        acc = 0;

    if (abs(acc) > 0.0005f)
        applyTorque(acc);
}

void RigidBody::setPosition(const vec2& pos)
{
    m_body->SetTransform({pos.x, pos.y}, getAngle());
}

void RigidBody::applyTorque(float torq)
{
    m_body->ApplyTorque(torq, true);
}

void RigidBody::applyLinearImpulse(const vec2& impulse)
{
    m_body->ApplyLinearImpulseToCenter({impulse.x, impulse.y}, true);
}

void RigidBody::fullStop()
{
    m_body->SetLinearVelocity({0,0});
}

vec2 RigidBody::getPosition() const
{
    auto pos = m_body->GetPosition();
    return {pos.x, pos.y};
}

vec2 RigidBody::getDirection() const
{
    float angle = getAngle();
    return {cosf(angle), sinf(angle)};
}

float RigidBody::getAngle() const
{
    return m_body->GetAngle();
}

vec2 RigidBody::getLinearVelocity() const
{
    auto vel = m_body->GetLinearVelocity();

    return {vel.x, vel.y};
}

void RigidBody::setUserData(void* id)
{
    m_body->SetUserData(id);
}

void* RigidBody::getUserData() const
{
    return m_body->GetUserData();
}

const RigidBody::Type& RigidBody::getType() const
{
    return m_type;
}