#include "RigidBody.hpp"

RigidBody::RigidBody(b2Body* bd, b2World* world)
    : body(bd), m_world(world)
{
}

RigidBody::~RigidBody()
{
    m_world->DestroyBody(body);
}