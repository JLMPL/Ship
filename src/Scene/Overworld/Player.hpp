#pragma once
#include "Spacecraft.hpp"
#include "Core/Timer.hpp"
#include <SFML/System/Time.hpp>

class Hud;

enum class Weapon
{
    BASIC,
    SHOTGUN,
    LASER,
    COUNT
};

class Player : public Spacecraft
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

    void addXp(int value);

    void onContact(SceneObject* other) override final;

private:
    // RigidBody::Ref m_body = nullptr;

    float m_heat = 0.f;
    sf::Time m_heatTimer;
    sf::Time m_shootTimer;

    // int m_health = 100;
    // int m_maxHealth = 100;

    bool m_overheat = false;

    Weapon m_weapon = Weapon::BASIC;

    Hud* m_hud = nullptr;

    int m_xp = 0;
    int m_xpToLevel = 500;

    vec2 m_rayhit;

    vec2 m_aim;

    // Mesh m_mesh;
    // Trail m_trail;

};