#pragma once
#include "Core/Math.hpp"
#include "Physics/RigidBody.hpp"

enum class ComponentMask
{
    Transform = 1 << 0,
    RigidBody = 1 << 1
};

struct TransformComp
{
    using Ptr = std::unique_ptr<TransformComp>;

    vec2 pos;
    float angle = 0.f;
};
