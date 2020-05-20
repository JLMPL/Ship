#include "Renderer.hpp"

void Renderer::init(sf::RenderWindow& window)
{
    m_window = &window;
}

void Renderer::draw(sf::Text& text)
{
    m_window->draw(text);
}

void Renderer::draw(sf::Vertex* verts, int num, sf::PrimitiveType type, const sf::RenderStates& rs)
{
    m_window->draw(verts, num, type, rs);
}

void Renderer::drawLine(const sf::Vector2f& a, const sf::Vector2f& b, const sf::Color& color)
{
    sf::Vertex line[2];
    line[0].position = a;
    line[0].color = color;

    line[1].position = b;
    line[1].color = color;

    m_window->draw(line, 2, sf::Lines);
}