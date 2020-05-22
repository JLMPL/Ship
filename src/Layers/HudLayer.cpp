#include "HudLayer.hpp"
#include "LayerStack.hpp"
#include "Renderer.hpp"
#include <cmath>

// FIXME: Hardcoded resolution

static constexpr float HeatBarHeight = 250.f;

static float l_heat = 0.f;

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
    float actual = (1080 - (HeatBarHeight + 32)) + (250.f - (l_heat * 2.5));

    m_rect.setPosition(m_rect.getPosition().x, actual);
}

void HudLayer::draw()
{
    Renderer::Get().draw(m_verts, 3, sf::Triangles);
    Renderer::Get().draw(m_rect);
}

void HudLayer::setHeat(float level)
{
    l_heat = std::min(std::max(level, 0.f), 100.f);
}