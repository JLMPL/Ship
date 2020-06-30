#pragma once
#include "Libs/box2d/box2d.h"
#include "Core/Math.hpp"
#include <memory>

class StaticBody
{
public:
    using Ptr = std::unique_ptr<StaticBody>;

    StaticBody(b2Body* bd, b2World* world);
    ~StaticBody();

    void setPosition(const vec2& pos);
    vec2 getPosition() const;

    void setUserData(int* id);
    int getUserData() const;

private:
    b2Body* m_body = nullptr;
    b2World* m_world = nullptr;
};