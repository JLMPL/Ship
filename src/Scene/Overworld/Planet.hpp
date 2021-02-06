#pragma once
#include "Scene/SceneObject.hpp"
#include "Physics/StaticBody.hpp"
#include "Visual/Mesh.hpp"

class Planet : public SceneObject
{
public:
    Planet(Scene* scene);
    ~Planet() = default;

    void ready(const vec2& spawnPoint = vec2(0,0));

    void update(float dt) override final;
    void draw() override final;

private:
    StaticBody::Ref m_body = nullptr;
    Mesh m_mesh;
};