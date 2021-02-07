#pragma once
#include "Scene/SceneObject.hpp"
#include "Physics/RigidBody.hpp"
#include "Visual/Mesh.hpp"
#include "Visual/Trail.hpp"

class Spacecraft : public SceneObject
{
public:
    Spacecraft(Scene* scene);

    void ready(bool player);
    void update(float dt) override;
    void draw() override;

    void setPosition(const vec2& pos) override final;

protected:
    RigidBody::Ref m_body = nullptr;
    int m_health = 100;
    int m_maxHealth = 100;

    Mesh m_mesh;
    Trail m_trail;
};