#include "BackgroundLayer.hpp"
#include "LayerStack.hpp"
#include "Renderer.hpp"
#include "Random.hpp"
#include <cmath>

static constexpr float ExtentsOfSpace = 10'000.0f;

BackgroundLayer::BackgroundLayer(LayerStack& layerStack)
    : Layer(layerStack)
{
    for (auto& star : m_stars)
    {
        star = sf::Vertex({
            rando::inRange(-ExtentsOfSpace, ExtentsOfSpace),
            rando::inRange(-ExtentsOfSpace, ExtentsOfSpace)
        });
    }

    for (auto& star : m_back)
    {
        star = sf::Vertex({
            rando::inRange(-ExtentsOfSpace, ExtentsOfSpace),
            rando::inRange(-ExtentsOfSpace, ExtentsOfSpace)},
            {192,192,192,255}
        );
    }

    for (auto& star : m_back2)
    {
        star = sf::Vertex({
            rando::inRange(-ExtentsOfSpace, ExtentsOfSpace),
            rando::inRange(-ExtentsOfSpace, ExtentsOfSpace)},
            {100,100,100,255}
        );
    }
}

void BackgroundLayer::update(float dt)
{
    m_time += dt;

    // for (auto& star : m_stars)
        // star.position += sf::Vector2f(cos(m_time), sin(m_time)) * 0.01f;

    // for (auto& star : m_back)
        // star.position += sf::Vector2f(cos(m_time), sin(m_time)) * 0.005f;

    // for (auto& star : m_back2)
        // star.position += sf::Vector2f(cos(m_time), sin(m_time)) * 0.00025f;
}

void BackgroundLayer::draw()
{
    Renderer::get().draw(&m_back2[0], m_back2.size(), sf::Points);
    Renderer::get().draw(&m_back[0], m_back.size(), sf::Points);
    Renderer::get().draw(&m_stars[0], m_stars.size(), sf::Points);
}

