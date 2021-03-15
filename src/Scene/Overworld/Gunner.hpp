#pragma once
#include "Spacecraft.hpp"
#include "Scene/UI/ProgressBar.hpp"
#include <SFML/System/Clock.hpp>

class Gunner : public Spacecraft
{
public:
    Gunner(Scene* scene);
    ~Gunner() = default;

    void ready(const vec2& spawnPoint = vec2(0,0));

    void update(float dt) override final;
    void draw() override final;

    void onContact(SceneObject* other) override final;

    void damage(int value);

private:
    void shoot();

private:
    SceneObject* m_player = nullptr;

    bool m_isDead = false;

    ProgressBar m_healthbar;

    vec2 m_spawnPoint;

    sf::Time m_shootTimer = sf::seconds(0);
    sf::Time m_stateTimer = sf::seconds(0);
    bool m_isShooting = false;
};