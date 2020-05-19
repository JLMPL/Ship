#include "GameLayer.hpp"
#include "LayerStack.hpp"
#include "Renderer.hpp"

GameLayer::GameLayer(LayerStack& layerStack)
    : Layer(layerStack)
{
    m_ship[0].position = {0,0};
    m_ship[1].position = {-10,48};
    m_ship[2].position = {0,32};
    m_ship[3].position = {10,48};
    m_ship[4].position = {0,0};
}

void GameLayer::update(float dt)
{
    m_physWorld.update(dt);
}

void GameLayer::draw()
{
    m_physWorld.draw();

    sf::Transform tr;
    tr.translate({200,200}).rotate(45);

    sf::RenderStates rs(tr);

    Renderer::Get().draw(&m_ship[0], m_ship.size(), sf::LineStrip, rs);
}

