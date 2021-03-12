#pragma once
#include "SceneObject.hpp"
#include <SFML/Graphics.hpp>
#include <array>

static constexpr int NumberOfStars = 200000;

class StarBackground : public SceneObject
{
public:
	StarBackground(Scene* scene);
    ~StarBackground() = default;

    void update(float dt) override final;
    void draw() override final;

private:
    std::array<sf::Vertex, NumberOfStars> m_stars;
    std::array<sf::Vertex, NumberOfStars> m_back;
    std::array<sf::Vertex, NumberOfStars> m_back2;

    float m_time = 0.f;
};