#pragma once
#include "Layer.hpp"
#include <SFML/Graphics.hpp>

class BackgroundLayer : public Layer
{
public:
    BackgroundLayer(LayerStack& ss);
    ~BackgroundLayer() = default;

    void update(float dt) override final;
    void draw() override final;

private:
    static constexpr uint NumberOfStars = 50'000u;
    std::array<sf::Vertex, NumberOfStars> m_stars;
    std::array<sf::Vertex, NumberOfStars> m_back;
    std::array<sf::Vertex, NumberOfStars> m_back2;

    float m_time = 0.f;
};