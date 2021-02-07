#include "Tutorial.hpp"
#include "Core/Config.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"
#include "Input/Input.hpp"

Tutorial::Tutorial(Scene* scene)
 : SceneObject(scene)
{
    m_name = "tutorial";
    m_pausable = false;
    m_font.loadFromFile("data/DejaVuSans.ttf");

    m_text.setFont(m_font);
    m_text.setCharacterSize(20);

    m_continue.setFont(m_font);
    m_continue.setCharacterSize(20);
    m_continue.setString(L"Press $3A$0 to continue");
    m_continue.setPosition({DisplayWidth /2 - m_continue.getSize().x/2, DisplayHeight - (m_continue.getSize().y + 24)});
}

void Tutorial::show(TutorialType tut)
{
    if (m_viewedAlready[tut])
        return;

    m_viewedAlready[tut] = true;

    switch (tut)
    {
        case TUTORIAL_HEALTH:
        {
            m_text.setString(
                L"$2Health: $0Keep it high and you'll be fine.\n"
                L"Beware though. If you fail... it's over - no second chances.\n\n"
                L"Engine Cooling: Make sure your engine is in a good state.\n"
                L"If it overheats, you will lose control unitl it becomes stable again.\n\n"
                L"$5Coordinates: $0Show your position within the system.\n"
                L"Standard tool for navigation.\n"
            );
            m_text.setPosition({24, DisplayHeight/2});

            m_highlight = {24, DisplayHeight - 120, 300, 100};
            break;
        }
        case TUTORIAL_OBJECTIVE:
        {
            m_text.setString(L"Be a good pirate and follow $3orders$0.\nIf you do what you're told, you can't go wrong.");
            m_text.setPosition({24, DisplayHeight/2});

            m_highlight = {24, 24, 300, 40};
            break;
        }
        case TUTORIAL_XP:
        {
            m_text.setString(L"As you $2kill$0 people you'll gain the necessary $6experience$0.\nLet's hope it will be worth it.");
            m_text.setPosition({24, DisplayHeight/2});

            m_highlight = {(DisplayWidth /2) - 180, 24, 180*2, 40};
            break;
        }
    }

    m_scene->setPause(true);
    m_visible = true;
}

void Tutorial::update(float dt)
{
    if (Input.get()->isConfirm())
    {
        m_scene->setPause(false);
        m_visible = false;
    }
}

void Tutorial::draw()
{
    if (!m_visible) return;

    sf::Color color(0,0,0,192);
    sf::Color black(0,0,0,255);

    sf::Vertex v00({0,0}, black);
    sf::Vertex v10({DisplayWidth, 0}, black);
    sf::Vertex v01({0, DisplayHeight}, black);
    sf::Vertex v11({DisplayWidth, DisplayHeight}, black);

    sf::Vertex h00({m_highlight.left, m_highlight.top}, color);
    sf::Vertex h10({m_highlight.left + m_highlight.width, m_highlight.top}, color);
    sf::Vertex h01({m_highlight.left, m_highlight.top + m_highlight.height}, color);
    sf::Vertex h11({m_highlight.left + m_highlight.width, m_highlight.top + m_highlight.height}, color);

    sf::Vertex verts[] = {
        h00,
        v10,
        v00,

        h00,
        h10,
        v10,

        h00,
        v00,
        v01,

        h01,
        h00,
        v01,

        h11,
        h01,
        v01,

        v11,
        h11,
        v01,

        v11,
        v10,
        h10,

        v11,
        h10,
        h11
    };

    Renderer::get().draw(verts, 24, sf::PrimitiveType::Triangles);
    m_text.draw();
    m_continue.draw();
}