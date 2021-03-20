#pragma once
#include "Scene/SceneObject.hpp"
#include "Visual/Mesh.hpp"

class Debris : public SceneObject
{
public:
    Debris(Scene* scene);
    ~Debris() = default;

    void ready(const vec2& pos, const sf::Color& color);
    void update(float dt) override final;
    void draw() override final;

private:
    Mesh m_mesh;
    float m_angle = 0.f;
    float m_scale = 0.5f;
    vec2 m_dir;

    float m_rotationSpeed = 1.f;
    float m_fallSpeed = 1.f;
};