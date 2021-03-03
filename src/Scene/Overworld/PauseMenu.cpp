#include "PauseMenu.hpp"
#include "Renderer.hpp"
#include "Input/Input.hpp"
#include "Scene/Scene.hpp"
#include "Core/Config.hpp"

PauseMenu::PauseMenu(Scene* scene)
    : SceneObject(scene)
{
    m_name = "pause_menu";
    m_pausable = false;

    m_font.loadFromFile("data/fonts/DejaVuSans.ttf");
    m_text.setFont(m_font);
    m_text.setCharacterSize(32);
    m_text.setString(L"Pause");
    m_text.setPosition({DisplayWidth/2, DisplayHeight/2});
    m_text.setOrigin(m_text.getSize() / 2.f);

    m_overlay.setSize({DisplayWidth, DisplayHeight});
    m_overlay.setFillColor({0,0,0,128});
}

void PauseMenu::update(float dt)
{
    m_timer += sf::seconds(dt);

    if (m_timer > sf::seconds(0.25) && Input.get()->isAction(Action::A_MENU))
    {
        m_isActive = !m_isActive;
        m_scene->setPause(m_isActive);
        m_timer = sf::seconds(0);
    }
}

void PauseMenu::draw()
{
    if (m_isActive)
    {
        Renderer.draw(m_overlay);
        m_text.draw();
    }
}
