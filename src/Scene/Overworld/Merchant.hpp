#pragma once
#include "Spacecraft.hpp"
#include "Scene/UI/ProgressBar.hpp"
#include <SFML/System/Clock.hpp>

class Merchant : public Spacecraft
{
public:
    Merchant(Scene* scene);
    ~Merchant() = default;

    void ready(const vec2& spawnPoint = vec2(0,0));

    void update(float dt) override final;
    void draw() override final;

    void onContact(SceneObject* other) override final;

    void damage(int value);

private:
    SceneObject* m_player = nullptr;

    bool m_isDead = false;

    ProgressBar m_healthbar;

    vec2 m_spawnPoint;
};