#include "GameOver.hpp"
#include "Core/Config.hpp"
#include "Renderer.hpp"

GameOver::GameOver(Scene* scene)
 : SceneObject(scene)
{
    m_name = "game_over";

    m_font.loadFromFile("data/fonts/DejaVuSans.ttf");

    m_text.setFont(m_font);
    m_text.setCharacterSize(64);
    m_text.setString(L"Game Over!");
    m_text.setOrigin(m_text.getSize() / 2.f);
    m_text.setPosition({DisplayWidth / 2, DisplayHeight / 2});
    m_text.setColor(sf::Color::Transparent);

    m_smol.setFont(m_font);
    m_smol.setCharacterSize(20);
    m_smol.setString(L"Better luck next time! Maybe...");
    m_smol.setOrigin(m_smol.getSize() / 2.f);
    m_smol.setPosition({DisplayWidth / 2, DisplayHeight * 0.75});
    m_smol.setColor(sf::Color::Transparent);

    m_overlay.setSize({DisplayWidth, DisplayHeight});
    m_overlay.setFillColor(sf::Color::Transparent);
}

void GameOver::update(float dt)
{
    if (!m_isActive) return;

    m_alpha = std::min(255.f, m_alpha + dt * 40);
    m_textAlpha = std::min(255.f, m_alpha + dt * 500);

    m_overlay.setFillColor(sf::Color(0,0,0, m_alpha));
    m_text.setColor(sf::Color(255,255,255, m_textAlpha));
    m_smol.setColor(sf::Color(255,255,255, m_textAlpha));
}

void GameOver::draw()
{
    if (!m_isActive) return;

    Renderer.draw(m_overlay);
    m_text.draw();
    m_smol.draw();
}

void GameOver::show()
{
    m_isActive = true;
}