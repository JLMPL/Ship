#include "HudLayer.hpp"
#include "LayerStack.hpp"
#include "Renderer.hpp"
#include "Core/Math.hpp"
#include "Core/Config.hpp"
#include <cmath>

static constexpr float HeatBarHeight = 250.f;

static constexpr float HealthBarHeight = 40.f;

static float l_heat = 0.f;

HudLayer::HudLayer(LayerStack& layerStack)
    : Layer(layerStack)
{
    m_rect.setSize({2, 16});
    m_rect.setOrigin({1, 11});
    m_rect.setPosition({32, DisplayHeight - (5 + 32 + HealthBarHeight + 5)});
    m_rect.setFillColor(sf::Color::White);

    m_hpBack.setSize({256, HealthBarHeight});
    m_hpBack.setPosition({32, DisplayHeight - (HealthBarHeight + 32)});
    m_hpBack.setFillColor({64,64,64,255});

    m_hp.setSize({256, HealthBarHeight});
    m_hp.setPosition({32, DisplayHeight - (HealthBarHeight + 32)});
    m_hp.setFillColor({192,192,192,255});
    m_hp.setScale({0.66, 1});

    m_heatBack.setSize({256, 5});
    m_heatBack.setPosition({32, DisplayHeight - (5 + 32 + HealthBarHeight + 5)});
    m_heatBack.setFillColor({64,64,64,255});

    m_heat.setSize({256, 5});
    m_heat.setPosition({32, DisplayHeight - (5 + 32 + HealthBarHeight + 5)});
    m_heat.setFillColor(sf::Color::White);

    m_font.loadFromFile("data/NotoSans-Regular.ttf");

    m_text.setFont(m_font);
    m_text.setCharacterSize(32);
    m_text.setFillColor(sf::Color::Red);
    m_text.setOutlineThickness(2);
    m_text.setOutlineColor({64,0,0,255});
    m_text.setString("ENGINE OVERHEATED!");
    m_text.setOrigin({m_text.getLocalBounds().width/2, 0});
    m_text.setPosition({DisplayWidth/2, (DisplayHeight/2) - 100});
}

void HudLayer::update(float dt)
{
    float actual = 32 + (256.f - (l_heat * 2.56));
    m_heat.setScale({1.f - (l_heat / 100.f), 1.f});

    m_rect.setPosition(actual, m_rect.getPosition().y);

    if (l_heat == 100.f)
        m_overheat = true;
    if (l_heat == 0.f)
        m_overheat = false;
}

void HudLayer::draw()
{
    Renderer::get().draw(m_hpBack);
    Renderer::get().draw(m_hp);
    Renderer::get().draw(m_heatBack);
    Renderer::get().draw(m_heat);
    Renderer::get().draw(m_rect);

    if (m_overheat)
        Renderer::get().draw(m_text);
}

void HudLayer::setHeat(float level)
{
    l_heat = std::min(std::max(level, 0.f), 100.f);
}