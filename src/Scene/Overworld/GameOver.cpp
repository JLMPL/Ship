#include "GameOver.hpp"
#include "../Scene.hpp" // somehow including this is absolutely necessary in MSVC
#include "Core/Config.hpp"
#include "Renderer.hpp"
#include "../Overworld.hpp"
#include "Input/Input.hpp"
#include "GameplayVars.hpp"

GameOver::GameOver(Scene* scene)
 : SceneObject(scene)
{
    m_name = "game_over";

    m_font.loadFromFile("data/fonts/nasalization.ttf");

    m_text.setFont(m_font);
    m_text.setCharacterSize(64);
    m_text.setString(L"Game Over!");
    m_text.setOrigin(m_text.getSize() / 2.f);
    m_text.setPosition({DisplayWidth / 2, DisplayHeight / 2});
    // m_text.setColor(sf::Color::Transparent);

    m_smol.setFont(m_font);
    m_smol.setCharacterSize(20);
    std::wstring mess = L"$0Your wallet contained $6" + std::to_wstring(gamevars::PlayerMoney) + L"$0 money units. Better luck next time! Maybe...";
    m_smol.setString(mess);
    m_smol.setOrigin(m_smol.getSize() / 2.f);
    m_smol.setPosition({DisplayWidth / 2, DisplayHeight * 0.75});
    // m_smol.setColor(sf::Color::Transparent);

    m_overlay.setSize({DisplayWidth, DisplayHeight});
    m_overlay.setFillColor(sf::Color::Transparent);

    m_skip.setFont(m_font);
    m_skip.setCharacterSize(20);
    m_skip.setString(L"$0Press $3[Enter] $0to rest in peace");
    m_skip.setOrigin({m_skip.getSize().x/2, m_skip.getSize().y});
    m_skip.setPosition({DisplayWidth/2, DisplayHeight-24});
}

void GameOver::update(float dt)
{
    if (!m_isActive) return;

    m_alpha = std::min(255.f, m_alpha + dt * 40);
    m_textAlpha = std::min(255.f, m_alpha + dt * 500);

    if (Input.get()->isAction(Action::A_CONFIRM))
    {
        static_cast<Overworld*>(m_scene)->goToMainMenu();
    }

    m_overlay.setFillColor(sf::Color(0,0,0, m_alpha));
    // m_text.setColor(sf::Color(255,255,255, m_textAlpha));
    // m_smol.setColor(sf::Color(255,255,255, m_textAlpha));
}

void GameOver::draw()
{
    if (!m_isActive) return;

    Renderer.draw(m_overlay);
    m_text.draw();
    m_smol.draw();
    m_skip.draw();
}

void GameOver::show()
{
    m_isActive = true;
    std::wstring mess = L"$0Your wallet contained $6" + std::to_wstring(gamevars::PlayerMoney) + L"$0 money units. Better luck next time! Maybe...";
    m_smol.setString(mess);
    m_smol.setOrigin(m_smol.getSize() / 2.f);
}