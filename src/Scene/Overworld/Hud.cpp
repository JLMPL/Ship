#include "Hud.hpp"
#include "Renderer.hpp"
#include "Core/Math.hpp"
#include "Core/Config.hpp"
#include <cmath>

static constexpr float HealthBarWidth = 250.f;
static constexpr float HealthBarHeight = 40.f;

static constexpr float XPBarWidth = 300.f;

Hud::Hud(Scene* scene)
    : SceneObject(scene)
{
    m_name = "hud";

    m_hpBar.setScaled(false);
    m_hpBar.setSize({HealthBarWidth, HealthBarHeight});
    m_hpBar.setColor({192,0,0,255});
    m_hpBar.setPosition({32, DisplayHeight - (HealthBarHeight + 32)});
    m_hpBar.setMaxValue(1000);
    m_hpBar.setValue(1000);

    m_heatBar.setScaled(false);
    m_heatBar.setSize({HealthBarWidth, 5});
    m_heatBar.setColor(sf::Color::White);
    m_heatBar.setPosition({32, DisplayHeight - (5 + 32 + HealthBarHeight + 5)});
    m_heatBar.setMaxValue(1000);
    m_heatBar.setValue(1000);

    m_font.loadFromFile("data/fonts/DejaVuSans.ttf");

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
    // m_coords.setFillColor(sf::Color::White);
    m_coords.setPosition({32, DisplayHeight - 112});

    //

    m_weaponsTex.loadFromFile("data/images/weapons.png");

    vec2 corner = {DisplayWidth - 128, DisplayHeight - 128};

    for (int i = 0; i < 4; i++)
    {
        m_weapons[i].setTexture(m_weaponsTex);
        m_weapons[i].setTextureRect({i*32,0,32,32});
    }

    m_weapons[0].setPosition(corner + vec2(32,64));
    m_weapons[1].setPosition(corner + vec2(64,32));
    m_weapons[2].setPosition(corner + vec2(32,0));
    m_weapons[3].setPosition(corner + vec2(0,32));

    m_money.setFont(m_font);
    m_money.setCharacterSize(24);
    m_money.setString(L"$6$ 0");
    m_money.setPosition({(DisplayWidth/2 - XPBarWidth/2) + 4, 24});
}

void Hud::update(float dt)
{
    m_heatBar.setValue(1000.f - m_heat * 10.f);

    if (m_heat == 100.f)
        m_overheat = true;
    if (m_heat == 0.f)
        m_overheat = false;

    m_hpBar.setValue(m_healthPercentage * 1000);
}

void Hud::draw()
{
    if (m_overheat)
        Renderer::get().draw(m_overheatText);

    m_coords.setString((L"$5") + std::to_wstring(m_playerCoords.x) + (L"$0 ⋅ $5") + std::to_wstring(m_playerCoords.y));
    m_coords.draw();

    for (int i = 0; i < 4; i++)
        Renderer::get().draw(m_weapons[i]);

    m_money.draw();

    m_hpBar.draw();
    m_heatBar.draw();
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

void Hud::setWeapon(int weapon)
{
    for (int i = 0; i < 4; i++)
    {
        m_weapons[i].setTextureRect({i*32, 32, 32,32});
    }

    m_weapons[weapon].setTextureRect({weapon*32, 0, 32,32});
}

void Hud::setMoney(int value)
{
    m_money.setString(L"$6$ " + std::to_wstring(value));
    m_money.setPosition({(DisplayWidth / 2) - (m_money.getSize().x / 2), 24});
}