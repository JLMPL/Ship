#pragma once
#include "Layer.hpp"
#include <SFML/Graphics.hpp>

class HudLayer : public Layer
{
public:
    HudLayer(LayerStack& ss);
    ~HudLayer() = default;

    void update(float dt) override final;
    void draw() override final;

private:
    sf::Vertex m_verts[3];
    sf::RectangleShape m_rect;
};