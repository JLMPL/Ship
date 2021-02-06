#pragma once
#include "Scene/SceneObject.hpp"
#include "Physics/RigidBody.hpp"
#include "Scene/UI/ProgressBar.hpp"
#include "Visual/Mesh.hpp"
#include <SFML/System/Clock.hpp>

class Merchant : public SceneObject
{
public:
    Merchant(Scene* scene);
    ~Merchant() = default;

    void ready(const vec2& spawnPoint = vec2(0,0));

    void update(float dt) override final;
    void draw() override final;

    void onContact(SceneObject* other) override final;

    void damage(int value);

    void setPosition(const vec2& pos) override final;

private:
    RigidBody::Ref m_body = nullptr;

    SceneObject* m_player = nullptr;

    int m_maxHealth = 500;
    int m_health = 500;
    bool m_isDead = false;

    ProgressBar m_healthbar;

    vec2 m_spawnPoint;
    Mesh m_mesh;
};