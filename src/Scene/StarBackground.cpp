#include "StarBackground.hpp"
#include "Renderer.hpp"
#include "Random.hpp"
#include "Scene.hpp"
#include <cmath>

static constexpr float ExtentsOfSpace = 1000.0f;

StarBackground::StarBackground(Scene* scene)
    : SceneObject(scene)
{
    for (auto& star : m_stars)
    {
        star = sf::Vertex({
            rng::inRange(-ExtentsOfSpace, ExtentsOfSpace),
            rng::inRange(-ExtentsOfSpace, ExtentsOfSpace)
        });
    }

    for (auto& star : m_back)
    {
        star = sf::Vertex({
            rng::inRange(-ExtentsOfSpace, ExtentsOfSpace),
            rng::inRange(-ExtentsOfSpace, ExtentsOfSpace)},
            {192,192,192,255}
        );
    }

    for (auto& star : m_back2)
    {
        star = sf::Vertex({
            rng::inRange(-ExtentsOfSpace, ExtentsOfSpace),
            rng::inRange(-ExtentsOfSpace, ExtentsOfSpace)},
            {100,100,100,255}
        );
    }
}

void StarBackground::update(float dt)
{
}

void StarBackground::draw()
{
    Renderer.drawScaled(&m_back2[0], m_back2.size(), sf::Points);
    Renderer.drawScaled(&m_back[0], m_back.size(), sf::Points);
    Renderer.drawScaled(&m_stars[0], m_stars.size(), sf::Points);
}

