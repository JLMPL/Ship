#include "Hud.hpp"
#include "Renderer.hpp"
#include "Core/Math.hpp"
#include "Core/Config.hpp"
#include <cmath>

// static constexpr float HeatBarHeight = 250.f;
static constexpr float HealthBarHeight = 40.f;

Hud::Hud(Scene* scene)
    : SceneObject(scene)
{
    m_name = "hud";

    m_hpBack.setSize({256, HealthBarHeight});
    m_hpBack.setPosition({32, DisplayHeight - (HealthBarHeight + 32)});
    m_hpBack.setFillColor({32,32,32,255});

    m_hp.setSize({256, HealthBarHeight});
    m_hp.setPosition({32, DisplayHeight - (HealthBarHeight + 32)});
    m_hp.setFillColor({192,192,192,255});

    m_heatBack.setSize({256, 5});
    m_heatBack.setPosition({32, DisplayHeight - (5 + 32 + HealthBarHeight + 5)});
    m_heatBack.setFillColor({32,32,32,255});

    m_heatRect.setSize({256, 5});
    m_heatRect.setPosition({32, DisplayHeight - (5 + 32 + HealthBarHeight + 5)});
    m_heatRect.setFillColor(sf::Color::White);

    m_font.loadFromFile("data/DejaVuSans.ttf");

    m_overheatText.setFont(m_font);
    m_overheatText.setCharacterSize(32);
    m_overheatText.setFillColor(sf::Color::Red);
    m_overheatText.setOutlineThickness(2);
    m_overheatText.setOutlineColor({64,0,0,255});
    m_overheatText.setString("ENGINE OVERHEATED!");
    m_overheatText.setOrigin({m_overheatText.getLocalBounds().width/2, 0});
    m_overheatText.setPosition({DisplayWidth/2, (DisplayHeight/2) - 100});

    m_coords.setFont(m_font);
    m_coords.setCharacterSize(24);
    m_coords.setFillColor(sf::Color::White);
    m_coords.setPosition({32, DisplayHeight - 112});
}

void Hud::update(float dt)
{
    m_heatRect.setScale({1.f - (m_heat / 100.f), 1.f});

    float heat1 = 1 - (m_heat / 100.f);
    m_heatRect.setFillColor({255, heat1 * 255, heat1 * 255, 255});

    if (m_heat == 100.f)
        m_overheat = true;
    if (m_heat == 0.f)
        m_overheat = false;

    m_hp.setScale({m_healthPercentage, 1});
}

void Hud::draw()
{
    Renderer::get().draw(m_hpBack);
    Renderer::get().draw(m_hp);
    Renderer::get().draw(m_heatBack);
    Renderer::get().draw(m_heatRect);

    if (m_overheat)
        Renderer::get().draw(m_overheatText);

    m_coords.setString(std::to_wstring(m_playerCoords.x) + (L" ⋅ ") + std::to_wstring(m_playerCoords.y));
    Renderer::get().draw(m_coords);
}

void Hud::setHeat(float level)
{
    m_heat = std::min(std::max(level, 0.f), 100.f);
}

void Hud::setHealthPercentage(float perc)
{
    m_healthPercentage = perc;
}

void Hud::setPlayerCoords(int x, int y)
{
    m_playerCoords = {x, y};
}