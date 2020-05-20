#include "GameLayer.hpp"
#include "LayerStack.hpp"
#include "Renderer.hpp"

GameLayer::GameLayer(LayerStack& layerStack)
    : Layer(layerStack)
{
    m_layerStack.push(Layer::Type::Hud);
}

void GameLayer::update(float dt)
{
    m_physWorld.update(dt);
}

void GameLayer::draw()
{
    m_physWorld.draw();
}

