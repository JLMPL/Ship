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
    static void setHealthPercentage(float perc);

private:
    sf::RectangleShape m_heatBack;
    sf::RectangleShape m_heat;
    sf::RectangleShape m_rect;
    sf::RectangleShape m_hpBack;
    sf::RectangleShape m_hp;

    sf::Font m_font;

    sf::Text m_overheatText;
    bool m_overheat = false;

    sf::Text m_mission;
    sf::Text m_objective[3];
};