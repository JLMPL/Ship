#pragma once
#include "Enemy.hpp"
#include <SFML/System/Time.hpp>

class Mothership : public Enemy
{
public:
    Mothership(Scene* scene);
    ~Mothership() = default;

    void ready(const vec2& spawnPoint = vec2(0,0));
    void update(float dt) override final;

private:
    vec2 m_spawnPoint;
    sf::Time m_clock;
};