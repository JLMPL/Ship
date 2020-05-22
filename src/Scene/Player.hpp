#pragma once
#include "Physics/RigidBody.hpp"
#include <SFML/System/Clock.hpp>

class PhysicsWorld;

class Player
{
public:
    Player(PhysicsWorld* pWorld);

    void update(float dt);
    void draw();

    void control(float dt);
    void shoot();

    void exertHeat(float heat);

private:
    PhysicsWorld* m_pWorld = nullptr;
    RigidBody* m_body = nullptr;

    float m_heat = 0.f;
    sf::Clock m_shootTimer;

    sf::Clock m_heatTimer;

    bool m_overheat = false;
};