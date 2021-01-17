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
    LASER,
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

    void addXp(int value);

    void setPosition(const vec2& pos) override final;

    void onContact(SceneObject* other) override final;

private:
    RigidBody::Ref m_body = nullptr;

    float m_heat = 0.f;
    sf::Time m_heatTimer;
    sf::Time m_shootTimer;

    int m_health = 100;
    int m_maxHealth = 100;

    bool m_overheat = false;

    Weapon m_weapon = Weapon::BASIC;

    Hud* m_hud = nullptr;

    int m_xp = 0;
    int m_xpToLevel = 500;

    vec2 m_rayhit;

    vec2 m_aim;

};