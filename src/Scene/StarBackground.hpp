#pragma once
#include "SceneObject.hpp"
#include <SFML/Graphics.hpp>
#include <array>

class StarBackground : public SceneObject
{
public:
    StarBackground(SceneContext* context);
    ~StarBackground() = default;

    void update(float dt) override final;
    void draw() override final;

private:
    static constexpr uint NumberOfStars = 200'000u;
    std::array<sf::Vertex, NumberOfStars> m_stars;
    std::array<sf::Vertex, NumberOfStars> m_back;
    std::array<sf::Vertex, NumberOfStars> m_back2;

    float m_time = 0.f;
};