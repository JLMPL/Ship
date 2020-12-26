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

private:
    RigidBody::Ref m_body = nullptr;

    SceneObject* m_player = nullptr;
};