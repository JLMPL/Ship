#include "Renderer.hpp"

void Renderer::init(sf::RenderWindow& window)
{
    m_window = &window;
}

void Renderer::draw(sf::Text& text)
{
    m_window->draw(text);
}

void Renderer::draw(sf::Vertex* verts, int num, sf::PrimitiveType type)
{
    m_window->draw(verts, num, type);
}