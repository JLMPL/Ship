#include "Objective.hpp"
#include "Core/Config.hpp"
#include "Scene/Scene.hpp"
#include "Random.hpp"
#include "Drone.hpp"

Objective::Objective(Scene* scene)
 : SceneObject(scene)
{
    m_font.loadFromFile("data/DejaVuSans.ttf");

    m_rtext.setFont(m_font);
    m_rtext.setCharacterSize(20);
    m_rtext.setPosition({24,24});
}

void Objective::generateNewObjective()
{
    m_complete = false;
    m_rtext.clear();
    // m_current = (ObjectiveType)rng::inRangei(0, 2);
    m_current = ObjectiveType::KILL_BANDITS;

    switch (m_current)
    {
        case KILL_BANDITS:
        {
            int numBandits = rng::inRangei(3,5);
            int x = rng::inRangei(-1000,1000);
            int y = rng::inRangei(-1000,1000);

            m_rtext << sf::Color::Red <<
                "Kill " << sf::Color::White <<
                std::to_string(numBandits) << " bandits " <<
                sf::Color::Yellow << "(" << std::to_string(x) << ", " <<
                std::to_string(y) << ")";

            for (int i = 0; i < numBandits; i++)
            {
                m_enemies.push_back(m_scene->spawnObject<Drone>(vec2(x,y)));
                Drone* dr = (Drone*)m_enemies.back();
                dr->setPosition({x,y});
            }
        }
        break;
    }
}

void Objective::checkCompletion()
{
    if (m_complete) return;

    switch (m_current)
    {
        case KILL_BANDITS:
        {
            if (m_enemies.size() == 0)
            {
                m_complete = true;
                m_timer.restart();
                m_rtext.clear();
                m_rtext << sf::Color::White << "Mission " << sf::Color::Green << "completed";
            }
        }
        break;
    }
}

void Objective::ready()
{
    generateNewObjective();
}

void Objective::update(float dt)
{
    checkCompletion();

    if (m_complete && m_timer.getElapsedTime() > sf::seconds(3))
    {
        generateNewObjective();
    }

    if (!m_enemies.empty())
    for (auto i = m_enemies.begin(); i != m_enemies.end();)
    {
        if ((*i)->isDestroyed())
            i = m_enemies.erase(i);
        else
            i++;
    }
}

void Objective::draw()
{
    Renderer::get().draw(m_rtext);
}
