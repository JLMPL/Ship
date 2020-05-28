#include "Renderer.hpp"

static constexpr float ViewScaling = 20.f;

void Renderer::init(sf::RenderWindow& window)
{
    m_window = &window;
}

void Renderer::draw(sf::Drawable& dw)
{
    m_window->setView(m_window->getDefaultView());
    m_window->draw(dw);
}

void Renderer::draw(sf::Vertex* verts, int num, sf::PrimitiveType type, const sf::RenderStates& rs)
{
    m_window->setView(m_window->getDefaultView());
    m_window->draw(verts, num, type, rs);
}

void Renderer::drawScaled(sf::Vertex* verts, int num, sf::PrimitiveType type, const sf::RenderStates& rs)
{
    m_window->setView(m_view);
    for (int i = 0; i < num; i++)
        verts[i].position *= ViewScaling;

    m_window->draw(verts, num, type, rs);
}

void Renderer::drawLineScaled(const sf::Vector2f& a, const sf::Vector2f& b, const sf::Color& color)
{
    m_window->setView(m_view);
    sf::Vertex line[2];
    line[0].position = a * ViewScaling;
    line[0].color = color;

    line[1].position = b * ViewScaling;
    line[1].color = color;

    m_window->draw(line, 2, sf::Lines);
}

// FIXME: Hardcoded resolution

void Renderer::setView(const sf::Vector2f& pos)
{
    m_view = sf::View(pos * ViewScaling, {1920,1080});
    m_window->setView(m_view);
}

sf::Vector2f Renderer::getGlobalMousePosition() const
{
    m_window->setView(m_view);
    auto mp = sf::Mouse::getPosition(*m_window);
    sf::Vector2f mousePos = {float(mp.x), float(mp.y)};

    mousePos.x += m_window->getView().getCenter().x - (1920/2);
    mousePos.y += m_window->getView().getCenter().y - (1080/2);

    mousePos /= ViewScaling;

    return mousePos;
}

sf::Vector2f Renderer::getLocalMousePosition() const
{
    auto mp = sf::Mouse::getPosition(*m_window);
    return {float(mp.x), float(mp.y)};
}