#pragma once
#include "Layer.hpp"
#include "Menu.hpp"

class MenuLayer : public Layer
{
public:
    MenuLayer(LayerStack& ss);
    ~MenuLayer() = default;

    void update(float dt) override final;
    void draw() override final;

private:
    sf::Font m_font;
    sf::Text m_title;

    Menu m_menu;
};