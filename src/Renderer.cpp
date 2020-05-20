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

void Renderer::setView(const sf::Vector2f& pos)
{
    sf::View view(pos * 32.f, {1280,720});
    m_window->setView(view);
}

sf::Vector2f Renderer::getGlobalMousePosition() const
{
    auto mp = sf::Mouse::getPosition(*m_window);
    sf::Vector2f mousePos = {float(mp.x), float(mp.y)};

    mousePos.x += m_window->getView().getCenter().x - (1280/2);
    mousePos.y += m_window->getView().getCenter().y - (720/2);

    mousePos /= 32.f;

    return mousePos;
}