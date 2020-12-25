#pragma once
#include "Scene/SceneObject.hpp"
#include "Physics/RigidBody.hpp"

class Drone : public SceneObject
{
public:
    Drone(SceneContext* context);
    ~Drone() = default;

    void update(float dt) override final;
    void draw() override final;

private:
    RigidBody* m_body = nullptr;

};