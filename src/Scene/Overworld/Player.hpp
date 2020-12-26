#pragma once
#include "Scene/SceneObject.hpp"
#include "Physics/RigidBody.hpp"
#include "Core/Timer.hpp"
#include <SFML/System/Clock.hpp>

class Hud;

enum class Weapon
{
    BASIC,
    SHOTGUN,
    COUNT
};

class Player : public SceneObject
{
public:
    Player(Scene* scene);
    ~Player() = default;

    void ready() override final;

    void update(float dt) override final;
    void draw() override final;

    void control();
    void exertHeat(float hdiff);
    void shoot();

private:
    RigidBody::Ref m_body = nullptr;

    float m_heat = 0.f;
    sf::Clock m_heatTimer;
    sf::Clock m_shootTimer;

    int m_health = 10;
    int m_maxHealth = 10;

    bool m_overheat = false;

    Weapon m_weapon = Weapon::BASIC;

    Hud* m_hud = nullptr;

};