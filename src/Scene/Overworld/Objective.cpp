#include "Objective.hpp"
#include "Core/Config.hpp"
#include "Scene/Scene.hpp"
#include "Random.hpp"
#include "Drone.hpp"
#include "Player.hpp"

Objective::Objective(Scene* scene)
 : SceneObject(scene)
{
    m_font.loadFromFile("data/DejaVuSans.ttf");

    m_obj.setFont(m_font);
    m_obj.setCharacterSize(20);
    m_obj.setPosition({24,24});
}

void Objective::generateNewObjective()
{
    m_complete = false;
    // m_current = (ObjectiveType)rng::inRangei(0, 2);
    m_current = ObjectiveType::KILL_BANDITS;

    switch (m_current)
    {
        case KILL_BANDITS:
        {
            int numBandits = rng::inRangei(3,5);
            // int x = rng::inRangei(-500,500);
            // int y = rng::inRangei(-500,500);

            int x = 40;
            int y = 0;

            std::wstring text = L"$2Kill $0" + std::to_wstring(numBandits) + L" bandits $5(" +
                std::to_wstring(x) + L", " + std::to_wstring(y) + L")";
            m_obj.setString(text);

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
                m_timer = sf::seconds(0);
                m_obj.setString(L"Mission $3completed");
                m_player->as<Player>()->addXp(200);
            }
        }
        break;
    }
}

void Objective::ready()
{
    m_player = m_scene->findObject("player_ship");

    generateNewObjective();
}

void Objective::update(float dt)
{
    m_timer += sf::seconds(dt);

    checkCompletion();

    if (m_complete && m_timer > sf::seconds(3))
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
    m_obj.draw();
}
