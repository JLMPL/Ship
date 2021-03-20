#pragma once
#include "Enemy.hpp"
#include "Scene/UI/ProgressBar.hpp"
#include <SFML/System/Clock.hpp>

class Merchant : public Enemy
{
public:
    Merchant(Scene* scene);
    ~Merchant() = default;

    void ready(const vec2& spawnPoint = vec2(0,0));

    void update(float dt) override final;

private:
    vec2 m_spawnPoint;
	vec2 m_target;
};