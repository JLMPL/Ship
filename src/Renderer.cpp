#include "Renderer.hpp"
#include "Core/Config.hpp"
#define STB_PERLIN_IMPLEMENTATION
#include "Libs/stb_perlin.h"

// static constexpr float ZoomCap = 0.07f;
static constexpr float ZoomCap = 0.2f;

void Renderer::init(sf::RenderWindow& window)
{
    m_window = &window;

    m_sceneTarget.create(DisplayWidth, DisplayHeight);
    m_uiTarget.create(DisplayWidth, DisplayHeight, false);

    setView({0,0});
    m_view.zoom(0.05f);
}

void Renderer::update()
{
    if (m_isShake)
    {
        float tim = m_shaker.getElapsedTime().asSeconds();

        if (tim > m_shakeDuration)
            m_isShake = false;

        tim += m_clock.getElapsedTime().asSeconds();
        tim *= 100.f;

        float x = stb_perlin_noise3(tim,-tim,-tim,0,0,0) * m_shakeStrength;
        float y = stb_perlin_noise3(-tim,tim,-tim,0,0,0) * m_shakeStrength;

        m_viewPos += vec2(x,y);
    }

    m_view = sf::View(m_viewPos, {DisplayWidth, DisplayHeight});
    m_view.zoom(m_zoom);
    m_sceneTarget.setView(m_view);
}

void Renderer::shake(float strength, float duration)
{
    m_isShake = true;
    m_shakeStrength = strength;
    m_shakeDuration = duration;
    m_shaker.restart();
}

void Renderer::clear()
{
    m_window->clear();
    // m_sceneTarget.clear(sf::Color(0x222034FF));
    m_sceneTarget.clear(sf::Color(0x000210ff));
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

void Renderer::drawLineScaled(const vec2& a, const vec2& b, const sf::Color& color)
{
    m_sceneTarget.setView(m_view);
    sf::Vertex line[2];
    line[0].position = a;
    line[0].color = color;

    line[1].position = b;
    line[1].color = color;

    m_sceneTarget.draw(line, 2, sf::Lines);
}

void Renderer::setView(const vec2& pos)
{
    m_viewPos = pos;
}

vec2 Renderer::getViewWorldPosition() const
{
    return m_view.getCenter();
}

vec2 Renderer::getGlobalMousePosition()
{
    m_sceneTarget.setView(m_view);
    auto mp = sf::Mouse::getPosition(*m_window);
    vec2 mousePos = {float(mp.x), float(mp.y)};

    mousePos.x += m_sceneTarget.getView().getCenter().x - (DisplayWidth/ 2);
    mousePos.y += m_sceneTarget.getView().getCenter().y - (DisplayHeight/ 2);

    return mousePos;
}

vec2 Renderer::getLocalMousePosition() const
{
    auto mp = sf::Mouse::getPosition(*m_window);
    return {float(mp.x), float(mp.y)};
}

void Renderer::setLocalMousePosition(const vec2& pos)
{
    sf::Mouse::setPosition({pos.x, pos.y}, *m_window);
}

void Renderer::setZoom(float zoom)
{
    m_zoom = 0.05f + zoom * 0.001;

    if (m_zoom > ZoomCap) m_zoom = ZoomCap;
}