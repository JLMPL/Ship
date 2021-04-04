#include "Objective.hpp"
#include "Core/Config.hpp"
#include "Scene/Scene.hpp"
#include "Random.hpp"
#include "Drone.hpp"
#include "Merchant.hpp"
#include "Player.hpp"
#include "Gunner.hpp"
#include "Kamikaze.hpp"
#include "Mothership.hpp"

static constexpr int BanditsValue = 200;
static constexpr int MerchantValue = 400;
static constexpr float ObjectiveExtents = 250.f;

Objective::Objective(Scene* scene)
 : SceneObject(scene)
{
	m_name = "objective";
    m_font.loadFromFile("data/fonts/nasalization.ttf");

    m_obj.setFont(m_font);
    m_obj.setCharacterSize(20);
    m_obj.setPosition({24,24});
}

void Objective::generateNewObjective()
{
    m_complete = false;
    m_current = (ObjectiveType)rng::inRangei(0, 2);

    // if (m_current == 0)
        // m_current = ObjectiveType::ROB_MERCHANT;
    // else
        // m_current = ObjectiveType::KILL_BANDITS;
        m_current = ObjectiveType::SURVIVE_TIME;

    switch (m_current)
    {
        case KILL_BANDITS:
        {
            int numDrones = rng::inRangei(m_droneNumber, m_droneNumber + 2);
            int numGunners = rng::inRangei(m_gunnerNumber, m_gunnerNumber);
            int numMothership = rng::inRangei(m_mothershipNumber, m_mothershipNumber);

            if (m_gunnerNumber <= 0)
                numGunners = 0;

            if (m_mothershipNumber <= 0)
                numMothership = 0;

			m_pos = vec2(rng::inRange(-ObjectiveExtents, ObjectiveExtents), rng::inRange(-ObjectiveExtents, ObjectiveExtents));
            m_pos = vec2(50, 0);

			std::wstring text = L"$2Rob $0" + std::to_wstring(numDrones + numGunners + numMothership) + L" losers";
            m_obj.setString(text);

            for (int i = 0; i < numDrones; i++)
            {
                auto dr = m_scene->spawnObject<Drone>(m_pos);
                dr->setPosition(m_pos);
            }

            for (int i = 0; i < numGunners; i++)
            {
                auto dr = m_scene->spawnObject<Gunner>(m_pos);
                dr->setPosition(m_pos);
            }

            for (int i = 0; i < numMothership; i++)
            {
                auto dr = m_scene->spawnObject<Mothership>(m_pos);
                dr->setPosition(m_pos);
            }
        }
        break;
        case ROB_MERCHANT:
        {
            std::wstring text = L"$4Rob $0Merchant";
            m_obj.setString(text);

            m_merchant = m_scene->spawnObject<Merchant>(vec2(40,0));
            m_merchant->setPosition(m_pos);

			// m_pos = vec2(40, 0);
            m_pos = vec2(rng::inRange(-ObjectiveExtents, ObjectiveExtents), rng::inRange(-ObjectiveExtents, ObjectiveExtents));
        }
        break;
        case SURVIVE_TIME:
        {
            std::wstring text = L"$5Survive $01:59";
            m_obj.setString(text);

            // m_surviveTimer = sf::seconds(rng::inRange(60, 90));
            m_surviveTimer = sf::seconds(rng::inRange(5, 10));
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
            if (m_scene->countObjectsByName("drone") == 0 &&
                m_scene->countObjectsByName("gunner") == 0 &&
                m_scene->countObjectsByName("mothership") == 0 &&
                m_scene->countObjectsByName("kamikaze") == 0)
            {
                m_complete = true;
                m_player->as<Player>()->addMoney(BanditsValue);

                m_droneNumber++;
                m_gunnerNumber++;
                m_mothershipNumber++;
            }
        }
        break;
        case ROB_MERCHANT:
        {
            if (m_scene->countObjectsByName("merchant") == 0)
            {
                m_complete = true;
                m_player->as<Player>()->addMoney(MerchantValue);
                m_merchant = nullptr;
            }
        }
        break;
        case SURVIVE_TIME:
        {
            if (int(m_surviveTimer.asSeconds()) == 0)
            {
                m_complete = true;
                m_player->as<Player>()->addMoney(200);
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

    if (m_current == SURVIVE_TIME && !m_complete)
    {
        m_surviveTimer -= sf::seconds(dt);

        int timer = int(m_surviveTimer.asSeconds());

        int minutes = (timer > 59) ? 1 : 0;
        int seconds = (timer > 59) ? timer - 60 : timer;

        std::wstring secondsStr = (seconds < 10) ? L"0" + std::to_wstring(seconds) : std::to_wstring(seconds);

        std::wstring text = L"$3Survive $0the attack - " + std::to_wstring(minutes) + L":" + secondsStr;
        m_obj.setString(text);
    }

    //if (m_current == ROB_MERCHANT && !m_complete)
    //{
    //    Merchant* mr = (Merchant*)m_enemies.back();
    //    vec2 pos = mr->getPosition();
    //    std::wstring text = L"$4Rob $0Merchant $5(" +
    //        std::to_wstring(int(pos.x)) + L", " + std::to_wstring(int(pos.y)) + L")";
    //    m_obj.setString(text);
    //}

    // printf("num_drones    %d\n", m_scene->countObjectsByName("drone"));
    // printf("num_merchants %d\n", m_scene->countObjectsByName("merchant"));

    // if (m_scene->countObjectsByName("drone") == 0 &&
    //     m_scene->countObjectsByName("merchant") == 0)
    // {
    //     m_enemies.clear();
    // }

    // if (!m_enemies.empty())
    // for (auto i = m_enemies.begin(); i != m_enemies.end();)
    // {
    //     if ((*i)->isDestroyed())
    //     {
    //         printf("Enemy died indeed!\n");
    //         i = m_enemies.erase(i);
    //     }
    //     else
    //         i++;
    // }
}

void Objective::draw()
{
    m_obj.draw();
}

const vec2& Objective::getPosition() const
{
	if (m_current == ROB_MERCHANT && m_merchant)
		return m_merchant->getPosition();

	return m_pos;
}