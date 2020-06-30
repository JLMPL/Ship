#include "HudLayer.hpp"
#include "LayerStack.hpp"
#include "Renderer.hpp"
#include "Core/Math.hpp"
#include "Core/Config.hpp"
#include <cmath>

static constexpr float HeatBarHeight = 250.f;
static constexpr float HealthBarHeight = 40.f;

static float l_heat = 0.f;
static float l_healthPercentage = 1.f;

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

    m_heatBack.setSize({256, 5});
    m_heatBack.setPosition({32, DisplayHeight - (5 + 32 + HealthBarHeight + 5)});
    m_heatBack.setFillColor({64,64,64,255});

    m_heat.setSize({256, 5});
    m_heat.setPosition({32, DisplayHeight - (5 + 32 + HealthBarHeight + 5)});
    m_heat.setFillColor(sf::Color::White);

    m_font.loadFromFile("data/NotoSans-Regular.ttf");

    m_overheatText.setFont(m_font);
    m_overheatText.setCharacterSize(32);
    m_overheatText.setFillColor(sf::Color::Red);
    m_overheatText.setOutlineThickness(2);
    m_overheatText.setOutlineColor({64,0,0,255});
    m_overheatText.setString("ENGINE OVERHEATED!");
    m_overheatText.setOrigin({m_overheatText.getLocalBounds().width/2, 0});
    m_overheatText.setPosition({DisplayWidth/2, (DisplayHeight/2) - 100});

    m_mission.setFont(m_font);
    m_mission.setCharacterSize(20);
    m_mission.setFillColor(sf::Color::Yellow);
    m_mission.setString("DESTROY THE CONVOY");
    m_mission.setPosition({32,32});

    for (int i = 0; i < 3; i++)
    {
        m_objective[i].setFont(m_font);
        m_objective[i].setCharacterSize(18);
        m_objective[i].setFillColor(sf::Color::White);
        m_objective[i].setPosition({48,0x40 + i * 32});
    }
    m_objective[0].setString("Destroy the Protector - 0/1");
    m_objective[1].setString("Destroy the Drones - 1/3");
    m_objective[2].setString("Destroy the Swarm - 0/1");
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

    m_hp.setScale({l_healthPercentage, 1});
}

void HudLayer::draw()
{
    Renderer::get().draw(m_hpBack);
    Renderer::get().draw(m_hp);
    Renderer::get().draw(m_heatBack);
    Renderer::get().draw(m_heat);
    Renderer::get().draw(m_rect);

    if (m_overheat)
        Renderer::get().draw(m_overheatText);

    Renderer::get().draw(m_mission);

    for (int i = 0; i < 3; i++)
        Renderer::get().draw(m_objective[i]);
}

void HudLayer::setHeat(float level)
{
    l_heat = std::min(std::max(level, 0.f), 100.f);
}

void HudLayer::setHealthPercentage(float perc)
{
    l_healthPercentage = perc;
}