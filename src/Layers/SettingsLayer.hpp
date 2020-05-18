#pragma once
#include "Layer.hpp"
#include "Menu.hpp"

class SettingsLayer : public Layer
{
public:
    SettingsLayer(LayerStack& ss);
    ~SettingsLayer() = default;

    void update(float dt) override final;
    void draw() override final;

private:
    sf::Font m_font;
    sf::Text m_title;
    sf::Text m_settings;

    Menu m_menu;
};