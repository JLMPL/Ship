#pragma once
#include "Layer.hpp"
#include "Menu.hpp"

class MenuBackgroundLayer : public Layer
{
public:
    MenuBackgroundLayer(LayerStack& ss);
    ~MenuBackgroundLayer() = default;

    void update(float dt) override final;
    void draw() override final;

private:
    std::array<sf::Vertex, 500> m_stars;
    std::array<sf::Vertex, 500> m_back;
    std::array<sf::Vertex, 500> m_back2;


    float m_time = 0.f;
};