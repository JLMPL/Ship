#include "Renderer.hpp"
#include "Core/Config.hpp"

static constexpr float ZoomCap = 0.07f;

void Renderer::init(sf::RenderWindow& window)
{
    m_window = &window;
    m_sceneTarget.create(DisplayWidth, DisplayHeight, false);
    m_uiTarget.create(DisplayWidth, DisplayHeight, false);

    setView({0,0});
    m_view.zoom(0.05f);
}

void Renderer::clear()
{
    m_window->clear();
    m_sceneTarget.clear(sf::Color::Black);
    m_uiTarget.clear(sf::Color::Transparent);
}

void Renderer::display()
{
    m_sceneTarget.display();
    m_uiTarget.display();

    sf::Sprite scene(m_sceneTarget.getTexture());
    // scene.setScale({2,2});
    m_window->draw(scene);

    sf::Sprite ui(m_uiTarget.getTexture());
    m_window->draw(ui);

    m_window->display();
}

void Renderer::draw(sf::Drawable& dw)
{
    m_uiTarget.setView(m_uiTarget.getDefaultView());
    m_uiTarget.draw(dw);
}

void Renderer::draw(sf::Vertex* verts, int num, sf::PrimitiveType type, const sf::RenderStates& rs)
{
    m_uiTarget.setView(m_uiTarget.getDefaultView());
    m_uiTarget.draw(verts, num, type, rs);
}

void Renderer::drawScaled(sf::Drawable& dw)
{
    m_sceneTarget.setView(m_view);
    m_sceneTarget.draw(dw);
}

void Renderer::drawScaled(sf::Vertex* verts, int num, sf::PrimitiveType type, const sf::RenderStates& rs)
{
    m_sceneTarget.setView(m_view);
    m_sceneTarget.draw(verts, num, type, rs);
}

void Renderer::drawLineScaled(const sf::Vector2f& a, const sf::Vector2f& b, const sf::Color& color)
{
    m_sceneTarget.setView(m_view);
    sf::Vertex line[2];
    line[0].position = a;
    line[0].color = color;

    line[1].position = b;
    line[1].color = color;

    m_sceneTarget.draw(line, 2, sf::Lines);
}

void Renderer::setView(const sf::Vector2f& pos)
{
    m_view = sf::View(pos, {DisplayWidth, DisplayHeight});
    m_view.zoom(m_zoom);
    m_sceneTarget.setView(m_view);
}

sf::Vector2f Renderer::getViewWorldPosition() const
{
    return m_view.getCenter();
}

sf::Vector2f Renderer::getGlobalMousePosition()
{
    m_sceneTarget.setView(m_view);
    auto mp = sf::Mouse::getPosition(*m_window);
    sf::Vector2f mousePos = {float(mp.x), float(mp.y)};

    mousePos.x += m_sceneTarget.getView().getCenter().x - (DisplayWidth/ 2);
    mousePos.y += m_sceneTarget.getView().getCenter().y - (DisplayHeight/ 2);

    return mousePos;
}

sf::Vector2f Renderer::getLocalMousePosition() const
{
    auto mp = sf::Mouse::getPosition(*m_window);
    return {float(mp.x), float(mp.y)};
}

void Renderer::setZoom(float zoom)
{
    m_zoom = 0.05f + zoom * 0.001;

    if (m_zoom > ZoomCap) m_zoom = ZoomCap;
}