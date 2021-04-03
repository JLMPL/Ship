#include "PauseMenu.hpp"
#include "Renderer.hpp"
#include "Input/Input.hpp"
#include "Scene/Scene.hpp"
#include "Core/Config.hpp"
#include "Player.hpp"
#include "GameplayVars.hpp"

PauseMenu::PauseMenu(Scene* scene)
    : SceneObject(scene)
{
    m_name = "pause_menu";
    m_pausable = false;

    m_font.loadFromFile("data/fonts/nasalization.ttf");
    m_text.setFont(m_font);
    m_text.setCharacterSize(48);
    m_text.setString(L"Pause");
    m_text.setPosition({float(DisplayWidth/2), float(DisplayHeight/2) - 100.f});
    m_text.setOrigin(m_text.getSize() / 2.f);

    m_overlay.setSize({float(DisplayWidth), float(DisplayHeight)});
    m_overlay.setFillColor({0,0,0,192});

    m_volumeBar.setSize({256,32});
    m_volumeBar.setMaxValue(100);
    m_volumeBar.setValue(50);
    m_volumeBar.setPosition({DisplayWidth/2 - 128, DisplayHeight/2 + 100});
    m_volumeBar.setScaled(false);

    m_volumeText.setFont(m_font);
    m_volumeText.setCharacterSize(20);
    m_volumeText.setString(L"SFX Volume");
    m_volumeText.setPosition({float(DisplayWidth/2), float(DisplayHeight/2) + 80.f});
    m_volumeText.setOrigin(m_volumeText.getSize() / 2.f);
}

void PauseMenu::update(float dt)
{
    if (!m_enabled) return;

    m_timer += sf::seconds(dt);

    if (m_timer > sf::seconds(0.25) &&
        Input.get()->isAction(Action::A_MENU) &&
        !m_scene->findObject<Player>("player_ship")->isDead())
    {
        m_isActive = !m_isActive;
        m_scene->setPause(m_isActive);
        m_timer = sf::seconds(0);
    }

    if (m_timer > sf::seconds(0.02))
    {
        if (Input.get()->isAction(Action::A_LEFT))
        {
            gamevars::SfxVolume = std::max(0, gamevars::SfxVolume - 1);
            m_timer = sf::seconds(0);
        }

        if (Input.get()->isAction(Action::A_RIGHT))
        {
            gamevars::SfxVolume = std::min(100, gamevars::SfxVolume + 1);
            m_timer = sf::seconds(0);
        }

        m_volumeBar.setValue(gamevars::SfxVolume);
    }
}

void PauseMenu::draw()
{
    if (m_isActive)
    {
        Renderer.draw(m_overlay);
        m_text.draw();

        m_volumeBar.draw();
        m_volumeText.draw();
    }
}

void PauseMenu::enable()
{
    m_enabled = true;
}