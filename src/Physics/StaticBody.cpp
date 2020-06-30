#include "StaticBody.hpp"

StaticBody::StaticBody(b2Body* bd, b2World* world)
    : m_body(bd), m_world(world)
{
}

StaticBody::~StaticBody()
{
    m_world->DestroyBody(m_body);
}

void StaticBody::setPosition(const vec2& pos)
{
    m_body->SetTransform({pos.x, pos.y}, 0);
}

vec2 StaticBody::getPosition() const
{
    auto pos = m_body->GetPosition();
    return {pos.x, pos.y};
}

void StaticBody::setUserData(int* id)
{
    m_body->SetUserData((void*)id);
}

int StaticBody::getUserData() const
{
    return *((int*)m_body->GetUserData());
}
