#pragma once
#include "Scene/SceneObject.hpp"
#include "Physics/RigidBody.hpp"
#include "Scene/UI/ProgressBar.hpp"
#include <SFML/System/Clock.hpp>

class Drone : public SceneObject
{
public:
    Drone(Scene* scene);
    ~Drone() = default;

    void ready(const vec2& spawnPoint = vec2(0,0));

    void update(float dt) override final;
    void draw() override final;

    void onContact(SceneObject* other) override final;

    void damage(int value);

    void setPosition(const vec2& pos) override final;

private:
    RigidBody::Ref m_body = nullptr;

    SceneObject* m_player = nullptr;

    int m_maxHealth = 100;
    int m_health = 100;
    bool m_isDead = false;

    ProgressBar m_healthbar;

    sf::Time m_clock;
    vec2 m_spawnPoint;
};