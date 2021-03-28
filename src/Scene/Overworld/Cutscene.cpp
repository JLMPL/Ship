#include "Cutscene.hpp"
#include "../Scene.hpp"
#include "Core/Config.hpp"
#include "Renderer.hpp"
#include "Input/Input.hpp"
#include "../Tutorial.hpp"
#include <array>

static const std::array<std::wstring, 11> text = {
    L"Long time ago...",
    L"In the distant future...",
    L"",
    L"There was a young Pirate.",
    L"A SPACE PIRATE!",
    L"",
    L"All he wanted to do is Kill and Plunder",
    L"So that's what he did...",
    L"Because he was a Pirate.",
    L"",
    L"Anyways..."
};

Cutscene::Cutscene(Scene* scene)
 : SceneObject(scene)
{
    m_name = "cutscene";
    m_pausable = false;

    m_overlay.setSize({DisplayWidth, DisplayHeight});
    m_overlay.setFillColor(sf::Color::Black);

    m_font.loadFromFile("data/fonts/nasalization.ttf");

    m_lines.resize(text.size());

    for (int i = 0; i < text.size(); i++)
    {
        m_lines[i].setFont(m_font);
        m_lines[i].setCharacterSize(32);
        m_lines[i].setString(text[i]);
        m_lines[i].setPosition({24, 100 + (i*40)});
        m_lines[i].setColor(sf::Color::Transparent);
    }

    m_skip.setFont(m_font);
    m_skip.setCharacterSize(20);
    m_skip.setString(L"$0Press $3[Enter] $0to skip...");
    m_skip.setOrigin({m_skip.getSize().x/2, m_skip.getSize().y});
    m_skip.setPosition({DisplayWidth/2, DisplayHeight-24});
}

void Cutscene::ready()
{
    m_scene->setPause(true);
}

void Cutscene::update(float dt)
{
    m_alpha = std::min(255.f, m_alpha + dt * 200);

    if (int(m_alpha) == 255)
    {
        m_index++;
        m_alpha = 0;
    }

    if (m_index <= m_lines.size()-1)
        m_lines[m_index].setColor(sf::Color(255,255,255,m_alpha));

    if (Input.get()->isAction(Action::A_CONFIRM))
    {
        m_scene->setPause(false);

        auto tut = m_scene->findObject<Tutorial>("tutorial");
        tut->show(TUTORIAL_OBJECTIVE);
        destroy();
    }
}

void Cutscene::draw()
{
    Renderer.draw(m_overlay);

    for (int i = 0; i < text.size(); i++)
    {
        m_lines[i].draw();
    }

    m_skip.draw();
}