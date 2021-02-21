#include "Objective.hpp"
#include "Core/Config.hpp"
#include "Scene/Scene.hpp"
#include "Random.hpp"
#include "Drone.hpp"
#include "Merchant.hpp"
#include "Player.hpp"

static constexpr int BanditsValue = 200;
static constexpr int MerchantValue = 400;

Objective::Objective(Scene* scene)
 : SceneObject(scene)
{
    m_font.loadFromFile("data/fonts/DejaVuSans.ttf");

    m_obj.setFont(m_font);
    m_obj.setCharacterSize(20);
    m_obj.setPosition({24,24});
}

void Objective::generateNewObjective()
{
    m_complete = false;
    m_current = (ObjectiveType)rng::inRangei(0, 1);
    m_current = ObjectiveType::KILL_BANDITS;

    switch (m_current)
    {
        case KILL_BANDITS:
        {
            int numBandits = rng::inRangei(3,25);
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
        case ROB_MERCHANT:
        {
            std::wstring text = L"$4Rob $0Merchant";
            m_obj.setString(text);

            m_enemies.push_back(m_scene->spawnObject<Merchant>(vec2(40,0)));
            Merchant* mr = (Merchant*)m_enemies.back();
            mr->setPosition({40,0});
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
                m_player->as<Player>()->addMoney(BanditsValue);
            }
        }
        break;
        case ROB_MERCHANT:
        {
            if (m_enemies.size() == 0)
            {
                m_complete = true;
                m_player->as<Player>()->addMoney(MerchantValue);
            }
        }
        break;
    }

    if (m_complete)
    {
        m_timer = sf::seconds(0);
        m_obj.setString(L"Mission $3completed");
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

    if (m_current == ROB_MERCHANT && !m_complete)
    {
        Merchant* mr = (Merchant*)m_enemies.back();
        vec2 pos = mr->getPosition();
        std::wstring text = L"$4Rob $0Merchant $5(" +
            std::to_wstring(int(pos.x)) + L", " + std::to_wstring(int(pos.y)) + L")";
        m_obj.setString(text);
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
