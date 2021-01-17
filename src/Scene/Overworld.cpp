#include "Overworld.hpp"
#include "Random.hpp"

#include "Overworld/Drone.hpp"
#include "Overworld/Player.hpp"
#include "Overworld/Hud.hpp"
#include "Overworld/Objective.hpp"
#include "StarBackground.hpp"
#include "Overworld/PauseMenu.hpp"

Overworld::Overworld(Game* game)
 : Scene(game)
{
    for (int i = 0; i < 1000; i++)
    {
        m_planets.push_back(m_physicsWorld.addStaticBody({
            rng::inRange(-1000.f, 1000.f),
            rng::inRange(-1000.f, 1000.f)},
            rng::inRange(2.f, 5.f)));
    }

    m_objects.emplace_back(new StarBackground(this));
    m_objects.emplace_back(new Player(this));

    for (int i = 0; i < 0; i++)
    {
        m_objects.emplace_back(new Drone(this));
        m_objects.back()->setPosition(vec2(i,0));
    }

    m_objects.emplace_back(new Objective(this));
    m_objects.emplace_back(new Hud(this));

    m_objects.emplace_back(new PauseMenu(this));

    ready();
}

// void Overworld::ready()
// {

// }

// void Overworld::update(float dt)
// {

// }

// void Overworld::draw()
// {

// }
