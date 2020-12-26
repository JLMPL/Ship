#pragma once
#include "Scene/SceneObject.hpp"
#include "Physics/RigidBody.hpp"

class Bullet : public SceneObject
{
public:
    Bullet(Scene* scene);
    ~Bullet() = default;

    void ready(const vec2& pos, const vec2& dir, bool player = false);
    void update(float dt) override final;
    void draw() override final;

private:
    RigidBody* m_body = nullptr;
};