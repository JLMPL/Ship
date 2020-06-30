#pragma once
#include "Core/Math.hpp"
#include "Physics/RigidBody.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

enum class ComponentMask
{
	Transform = 1 << 0,
	RigidBody = 1 << 1,
	Health = 1 << 2
};

struct TransformComp
{
    using Ptr = std::unique_ptr<TransformComp>;

    vec2 pos;
    float angle = 0.f;
};

struct HealthComp
{
	using Ptr = std::unique_ptr<HealthComp>;

    int maxHp = 1;
	int hp = 1;
    bool isDead = false;
};
