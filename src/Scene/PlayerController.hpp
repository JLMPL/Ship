#pragma once
#include "Controller.hpp"
#include "Physics/RigidBody.hpp"
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
    RigidBody* m_body = nullptr;

    float m_heat = 0.f;
    sf::Clock m_shootTimer;

    sf::Clock m_heatTimer;

    bool m_overheat = false;
};