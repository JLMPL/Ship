#include "MenuBackgroundLayer.hpp"
#include "LayerStack.hpp"
#include "Renderer.hpp"
#include "Random.hpp"
#include <cmath>

MenuBackgroundLayer::MenuBackgroundLayer(LayerStack& layerStack)
    : Layer(layerStack)
{
    for (auto& star : m_stars)
        star = sf::Vertex({rando::inRange(-100.f, 1400.f), rando::inRange(-100.f, 900.f)});

    for (auto& star : m_back)
        star = sf::Vertex({rando::inRange(-100.f, 1400.f), rando::inRange(-100.f, 900.f)}, {192,192,192,255});

    for (auto& star : m_back2)
        star = sf::Vertex({rando::inRange(-100.f, 1400.f), rando::inRange(-100.f, 900.f)}, {100,100,100,255});
}

void MenuBackgroundLayer::update(float dt)
{
    m_time += dt;

    for (auto& star : m_stars)
        star.position += sf::Vector2f(cos(m_time), sin(m_time)) * 0.01f;

    for (auto& star : m_back)
        star.position += sf::Vector2f(cos(m_time), sin(m_time)) * 0.005f;

    for (auto& star : m_back2)
        star.position += sf::Vector2f(cos(m_time), sin(m_time)) * 0.00025f;
}

void MenuBackgroundLayer::draw()
{
    Renderer::Get().draw(&m_back2[0], m_back2.size(), sf::Points);
    Renderer::Get().draw(&m_back[0], m_back.size(), sf::Points);
    Renderer::Get().draw(&m_stars[0], m_stars.size(), sf::Points);
}

