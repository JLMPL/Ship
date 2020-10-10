#pragma once
#include "Core/Math.hpp"
#include <memory>

struct SceneContext;

class Entity
{
public:
    using Ptr = std::unique_ptr<Entity>;

    Entity(SceneContext* context)
     : m_sContext(context) {}
    virtual ~Entity() {};

    virtual void update(float dt) = 0;
    virtual void draw() = 0;

    vec2 getPosition() const;

protected:
    SceneContext* m_sContext = nullptr;
    vec2 m_pos;
};

