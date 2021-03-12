#pragma once
#include "Spacecraft.hpp"
#include "Core/Timer.hpp"
#include <SFML/System/Time.hpp>
#include "Visual/Thruster.hpp"

class Hud;

enum class Weapon
{
    BASIC,
    SHOTGUN,
    LASER,
	ROCKETS,
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

    void addMoney(int value);

    void onContact(SceneObject* other) override final;

private:
    float m_heat = 0.f;
    sf::Time m_heatTimer;
    sf::Time m_shootTimer;

    bool m_overheat = false;
    Weapon m_weapon = Weapon::BASIC;

    Hud* m_hud = nullptr;

    vec2 m_rayhit;
    vec2 m_aim;

	Mesh m_arrow;
};