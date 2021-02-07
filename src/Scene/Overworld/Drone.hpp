#pragma once
#include "Spacecraft.hpp"
#include "Scene/UI/ProgressBar.hpp"
#include <SFML/System/Clock.hpp>

class Drone : public Spacecraft
{
public:
    Drone(Scene* scene);
    ~Drone() = default;

    void ready(const vec2& spawnPoint = vec2(0,0));

    void update(float dt) override final;
    void draw() override final;

    void onContact(SceneObject* other) override final;

    void damage(int value);

private:
    SceneObject* m_player = nullptr;

    bool m_isDead = false;

    ProgressBar m_healthbar;

    sf::Time m_clock;
    vec2 m_spawnPoint;
};