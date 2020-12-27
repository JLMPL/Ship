#pragma once
#include "Scene/SceneObject.hpp"
#include "Physics/RigidBody.hpp"

class Drone : public SceneObject
{
public:
    Drone(Scene* scene);
    ~Drone() = default;

    void update(float dt) override final;
    void draw() override final;

    void onContact(SceneObject* other) override final;

private:
    RigidBody::Ref m_body = nullptr;

    SceneObject* m_player = nullptr;

    int m_maxHealth = 10;
    int m_health = 10;
};