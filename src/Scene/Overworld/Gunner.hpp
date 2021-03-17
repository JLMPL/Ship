#pragma once
#include "Enemy.hpp"
#include "Scene/UI/ProgressBar.hpp"
#include <SFML/System/Clock.hpp>

class Gunner : public Enemy
{
public:
    Gunner(Scene* scene);
    ~Gunner() = default;

    void ready(const vec2& spawnPoint = vec2(0,0));

    void update(float dt) override final;

private:
    void shoot();

private:
    vec2 m_spawnPoint;

    sf::Time m_shootTimer = sf::seconds(0);
    sf::Time m_stateTimer = sf::seconds(0);
    bool m_isShooting = false;
};