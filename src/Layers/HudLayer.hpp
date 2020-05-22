#pragma once
#include "Layer.hpp"
#include <SFML/Graphics.hpp>
#include <functional>

class HudLayer : public Layer
{
public:
    HudLayer(LayerStack& ss);
    ~HudLayer() = default;

    void update(float dt) override final;
    void draw() override final;

    static void setHeat(float level);

private:
    sf::Vertex m_verts[3];
    sf::RectangleShape m_rect;

    sf::Font m_font;
    sf::Text m_text;
    bool m_overheat = false;
};