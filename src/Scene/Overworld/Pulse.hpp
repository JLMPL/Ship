#pragma once
#include "Scene/SceneObject.hpp"
#include <SFML/Graphics/CircleShape.hpp>

class Pulse : public SceneObject
{
public:
    Pulse(Scene* scene);
    ~Pulse() = default;

    void ready(const vec2& pos);
    void update(float dt) override final;
    void draw() override final;

private:
    float m_radius = 2.f;
    sf::Color m_color = sf::Color::Blue;

    sf::CircleShape m_circle;
};