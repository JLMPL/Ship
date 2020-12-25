#include "StarBackground.hpp"
#include "Renderer.hpp"
#include "Random.hpp"
#include <cmath>

static constexpr float ExtentsOfSpace = 1000.0f;

StarBackground::StarBackground(SceneContext* context)
    : SceneObject(context)
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

void StarBackground::update(float dt)
{
}

void StarBackground::draw()
{
    Renderer::get().drawScaled(&m_back2[0], m_back2.size(), sf::Points);
    Renderer::get().drawScaled(&m_back[0], m_back.size(), sf::Points);
    Renderer::get().drawScaled(&m_stars[0], m_stars.size(), sf::Points);
}

