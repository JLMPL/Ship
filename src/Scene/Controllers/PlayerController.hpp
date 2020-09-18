#pragma once
#include "Scene/Controller.hpp"
#include "Physics/RigidBody.hpp"
#include "Scene/Components.hpp"

#include <SFML/System/Clock.hpp>

class PlayerController : public Controller
{
public:
    PlayerController(Scene* scene, int id);
    ~PlayerController() = default;

    void update(float dt) override final;

private:
    void shoot();
    void control(float dt);
    void exertHeat(float amount);

private:
    TransformComp* m_tr = nullptr;
    RigidBody* m_body = nullptr;
    HealthComp* m_health = nullptr;

    float m_heat = 0.f;
    sf::Clock m_heatTimer;

    sf::Clock m_shootTimer;

    bool m_overheat = false;
};