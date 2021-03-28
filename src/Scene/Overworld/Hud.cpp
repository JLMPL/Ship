#include "Hud.hpp"
#include "Renderer.hpp"
#include "Core/Math.hpp"
#include "Core/Config.hpp"
#include "../Scene.hpp" // somehow including this is absolutely necessary in MSVC
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

    m_font.loadFromFile("data/fonts/nasalization.ttf");

    m_overheatText.setFont(m_font);
    m_overheatText.setCharacterSize(32);
    m_overheatText.setString(L"ENGINE OVERHEATED!");
    m_overheatText.setColor(sf::Color::Red);
    m_overheatText.setOrigin({m_overheatText.getSize().x/2, 0});
    m_overheatText.setPosition({float(DisplayWidth/2), float(DisplayHeight/2) - 100});

    //

    m_money.setFont(m_font);
    m_money.setCharacterSize(24);
    m_money.setString(L"$6$ 0");
    m_money.setPosition({(DisplayWidth/2 - XPBarWidth/2) + 4, 24});

	m_wheel[0].loadFromFile("data/meshes/weapon_wheel_down.obj");
	m_wheel[1].loadFromFile("data/meshes/weapon_wheel_right.obj");
	m_wheel[2].loadFromFile("data/meshes/weapon_wheel_up.obj");
	m_wheel[3].loadFromFile("data/meshes/weapon_wheel_left.obj");
	m_wheelShadow[0].loadFromFile("data/meshes/weapon_wheel_down.obj");
	m_wheelShadow[1].loadFromFile("data/meshes/weapon_wheel_right.obj");
	m_wheelShadow[2].loadFromFile("data/meshes/weapon_wheel_up.obj");
	m_wheelShadow[3].loadFromFile("data/meshes/weapon_wheel_left.obj");

	for (int i = 0; i < 4; i++)
	{
		m_wheel[i].setScale(50.f);
		m_wheelShadow[i].setScale(50.f);

		m_wheel[i].setPosition(vec2(DisplayWidth - 70.f, DisplayHeight - 70.f));
		m_wheelShadow[i].setPosition(vec2(DisplayWidth - 69.f, DisplayHeight - 69.f));
	}

    m_outOfBounds.setFont(m_font);
    m_outOfBounds.setCharacterSize(20);
    m_outOfBounds.setString(L"That's quite far enough Captain! Let's turn around.");
    m_outOfBounds.setOrigin(m_outOfBounds.getSize() / 2.f);
    m_outOfBounds.setPosition({DisplayWidth/2, DisplayHeight * 0.75f});

    m_weaponName.setFont(m_font);
    m_weaponName.setCharacterSize(20);
    m_weaponName.setString(L"Blaster");
    m_weaponName.setPosition({DisplayWidth - 130, DisplayHeight - 24});
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
        m_overheatText.draw();
        // Renderer.draw(m_overheatText);

    //for (int i = 0; i < 4; i++)
    //    Renderer.draw(m_weapons[i]);

    m_money.draw();

    m_hpBar.draw();
    m_heatBar.draw();

	for (int i = 0; i < 4; i++)
	{
		m_wheelShadow[i].draw(false);
		m_wheel[i].draw(false);
	}

    m_weaponName.draw();

    if (m_isOutOfBounds)
    {
        m_outOfBounds.draw();
    }
}

void Hud::setHeat(float level)
{
    m_heat = std::min(std::max(level, 0.f), 100.f);
}

void Hud::setHealthPercentage(float perc)
{
    m_healthPercentage = perc;
}

void Hud::setWeapon(int weapon)
{
    for (int i = 0; i < 4; i++)
    {
		m_wheel[i].setColor(sf::Color::Black);
		m_wheelShadow[i].setColor(sf::Color::White);
    }

	m_wheel[weapon].setColor(sf::Color::White);
	m_wheelShadow[weapon].setColor(sf::Color::Black);

    switch (weapon)
    {
        case 0:
            m_weaponName.setString(L"Blaster");
            break;
        case 1:
            m_weaponName.setString(L"Shotgun like blaster");
            break;
        case 2:
            m_weaponName.setString(L"Laser");
            break;
        case 3:
            m_weaponName.setString(L"Rockets");
            break;
    }

    m_weaponName.setOrigin(m_weaponName.getSize());
    m_weaponName.setPosition({DisplayWidth - 130, DisplayHeight - 24});
}

void Hud::setMoney(int value)
{
    m_money.setString(L"$6$ " + std::to_wstring(value));
    m_money.setPosition({(DisplayWidth / 2) - (m_money.getSize().x / 2), 24});
}

void Hud::setShowOutOfBounds(bool value)
{
    m_isOutOfBounds = value;
}