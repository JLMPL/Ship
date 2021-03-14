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
	m_name = "objective";
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
    // m_current = ObjectiveType::ROB_MERCHANT;

    switch (m_current)
    {
        case KILL_BANDITS:
        {
            int numBandits = rng::inRangei(3,5);
			//m_pos = vec2(rng::inRangei(-500, 500), rng::inRangei(-500, 500));

			m_pos = vec2(40, 0);

			std::wstring text = L"$2Kill $0" + std::to_wstring(numBandits) + L" bandits";
            m_obj.setString(text);

            for (int i = 0; i < numBandits; i++)
            {
                auto dr = m_scene->spawnObject<Drone>(m_pos);
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

			m_pos = vec2(40, 0);
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
            if (m_scene->countObjectsByName("drone") == 0)
            {
                m_complete = true;
                m_player->as<Player>()->addMoney(BanditsValue);
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