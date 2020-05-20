#include "HudLayer.hpp"
#include "LayerStack.hpp"
#include "Renderer.hpp"

// FIXME: Hardcoded resolution

static constexpr float HeatBarHeight = 250.f;

HudLayer::HudLayer(LayerStack& layerStack)
    : Layer(layerStack)
{
    m_rect.setSize({32, 2});
    m_rect.setPosition({32, 1080 - (125 + 32)});
    m_rect.setFillColor(sf::Color::White);

    m_verts[0].position = {64, 1080 - (HeatBarHeight + 32)};
    m_verts[0].color = sf::Color::Red;
    m_verts[1].position = {32, 1080 - (HeatBarHeight + 32)};
    m_verts[1].color = sf::Color::Red;
    m_verts[2].position = {32, 1080 - 32};
    m_verts[2].color = {0, 192, 255, 255};
}

void HudLayer::update(float dt)
{
}

void HudLayer::draw()
{
    Renderer::Get().draw(m_verts, 3, sf::Triangles);
    Renderer::Get().draw(m_rect);
}

