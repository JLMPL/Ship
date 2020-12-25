#pragma once
#include "Core/Math.hpp"
#include <memory>

struct SceneContext;

class SceneObject
{
public:
    using Ptr = std::unique_ptr<SceneObject>;

    SceneObject(SceneContext* context)
     : m_sContext(context) {}
    virtual ~SceneObject() {};

    virtual void update(float dt) = 0;
    virtual void draw() = 0;

    vec2 getPosition() const;

protected:
    SceneContext* m_sContext = nullptr;
    vec2 m_pos;
};

