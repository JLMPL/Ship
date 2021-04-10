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
#include "Attacker.hpp"
#include "Client.hpp"
#include "Bully.hpp"

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

    ObjectiveType previous = m_current;
    while (previous == m_current)
    {
        m_current = (ObjectiveType)rng::inRangei(0, 2);
    }

    // if (m_current == 0)
        m_current = ObjectiveType::PROTECT_CLIENT;
    // else
        // m_current = ObjectiveType::KILL_BANDITS;
        // m_current = ObjectiveType::SURVIVE_TIME;

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
            m_surviveTimer = sf::seconds(rng::inRange(30, 40));

            // for (int i = 0; i < 2; i++)
            // {
            //     auto dr = m_scene->spawnObject<Attacker>(m_pos);
            //     dr->setPosition(m_pos);
            // }
        }
        break;
        case PROTECT_CLIENT:
        {
            int bullies = rng::inRangei(m_maxBullies, m_maxBullies + 2);

            m_pos = vec2(rng::inRange(-ObjectiveExtents, ObjectiveExtents), rng::inRange(-ObjectiveExtents, ObjectiveExtents));

            m_currentBullies = bullies;

            std::wstring text = L"$8Protect $0your client from the suckers\n  " +
                std::to_wstring(m_currentBullies) + L" suckers remaining";
            m_obj.setString(text);

            m_client = m_scene->spawnObject<Client>(m_pos);
            m_client->setPosition(m_pos);

            for (int i = 0; i < bullies; i++)
            {
                vec2 offset = m_pos + vec2(rng::inRange(-20.f, 20.f), rng::inRange(-20.f, 20.f));
                auto dr = m_scene->spawnObject<Bully>(offset);
                dr->setPosition(offset);
            }
        }
        break;
    }

    m_timer = sf::seconds(0);
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

                auto remains = m_scene->findObjectsByName<Enemy>("attacker");

                for (auto& attacker : remains)
                {
                    attacker->kill();
                }

                m_surviveIntensity = std::max(1.f, m_surviveIntensity - 0.5f);
            }
        }
        break;
        case PROTECT_CLIENT:
        {
            if (m_currentBullies == 0)
            {
                m_complete = true;
                m_player->as<Player>()->addMoney(230);
                m_maxBullies++;

                m_scene->findObject<Client>("client")->goAway();
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

    if (m_timer > sf::seconds(0.5))
        checkCompletion();

    if (m_complete && m_timer > sf::seconds(3))
    {
        generateNewObjective();
    }

    if (m_current == SURVIVE_TIME && !m_complete)
    {
        m_surviveTimer -= sf::seconds(dt);
        m_surviveSpawner += sf::seconds(dt);

        int timer = int(m_surviveTimer.asSeconds());

        int minutes = (timer > 59) ? 1 : 0;
        int seconds = (timer > 59) ? timer - 60 : timer;

        std::wstring secondsStr = (seconds < 10) ? L"0" + std::to_wstring(seconds) : std::to_wstring(seconds);

        std::wstring text = L"$3Survive $0the attack - " + std::to_wstring(minutes) + L":" + secondsStr;
        m_obj.setString(text);

        if (m_surviveSpawner > sf::seconds(m_surviveIntensity))
        {
            auto dr = m_scene->spawnObject<Attacker>(m_pos);
            dr->setPosition(m_player->getPosition() + vec2(rng::inRange(-100, 100), rng::inRange(-100, 100)));
            m_surviveSpawner = sf::seconds(0);
        }
    }
    if (m_current == PROTECT_CLIENT && !m_complete)
    {
        std::wstring text = L"$8Protect $0your client from the suckers\n  " +
            std::to_wstring(m_currentBullies) + L" suckers remaining";
        m_obj.setString(text);

        m_currentBullies = m_scene->countObjectsByName("bully");

        // if (m_surviveSpawner > sf::seconds(m_surviveIntensity))
        // {
        //     auto dr = m_scene->spawnObject<Bully>(m_pos);
        //     dr->setPosition(m_player->getPosition() + vec2(rng::inRange(-100, 100), rng::inRange(-100, 100)));
        //     m_surviveSpawner = sf::seconds(0);
        // }

        m_pos = m_client->getPosition();
    }
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