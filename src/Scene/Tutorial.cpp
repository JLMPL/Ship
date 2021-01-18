#include "Tutorial.hpp"
#include "Core/Config.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"

Tutorial::Tutorial(Scene* scene)
 : SceneObject(scene)
{
    m_name = "tutorial";
    m_pausable = false;
    m_font.loadFromFile("data/DejaVuSans.ttf");

    m_text.setFont(m_font);
    m_text.setCharacterSize(20);
    m_text.setString(L"Ship's Health / Engine / Coordinates");
    m_text.setPosition({24, DisplayHeight/2});

    m_highlight.left = 24;
    m_highlight.top = DisplayHeight - 120;
    m_highlight.width = 300;
    m_highlight.height = 100;
}

void Tutorial::show(TutorialType tut)
{
    m_scene->setPause(true);
    m_visible = true;
}

void Tutorial::update(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        m_scene->setPause(false);
        m_visible = false;
    }
}

void Tutorial::draw()
{
    if (!m_visible) return;

    sf::Color color(0,0,0,192);

    sf::Vertex v00({0,0}, color);
    sf::Vertex v10({DisplayWidth, 0}, color);
    sf::Vertex v01({0, DisplayHeight}, color);
    sf::Vertex v11({DisplayWidth, DisplayHeight}, color);

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
}
