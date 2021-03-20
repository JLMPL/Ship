#include "Store.hpp"
#include "Renderer.hpp"
#include "Core/Config.hpp"
#include "Input/Input.hpp"
#include "Scene/Scene.hpp"
#include "Hud.hpp"
#include "GameplayVars.hpp"
#include "Player.hpp"

static constexpr float ScreenFract = 0.6;
static constexpr float PositionFract = (1.f - ScreenFract) / 2.f;

Store::Store(Scene* scene)
 : SceneObject(scene)
{
    m_name = "Store";
    m_pausable = false;

    m_overlay.setSize({DisplayWidth * ScreenFract, DisplayHeight * ScreenFract});
    m_overlay.setPosition({DisplayWidth * PositionFract, DisplayHeight * PositionFract});
    m_overlay.setFillColor(sf::Color(0,0,0,255));

    m_items[0].setData(L"Blaster Spread", L"Shoots a wide cone of bolts covering a large area.\nVery effective at short distance.", 1520);
    m_items[1].setData(L"Laser", L"Deals continous damage in a straight line.\nEffective at a long distance.", 3210);
    m_items[2].setData(L"Homing Rockets", L"Rockets automatically homing towards closest\nenemies. Effective against groups.", 5560);
    m_items[3].setData(L"Ultra Brakes", L"Stops any and all momentum on the ship.\nHuge power cost.", 2310);
    m_items[4].setData(L"Heal", L"Fully restores health.", 500);

    float itemHeight = (DisplayHeight * ScreenFract) / ITEM_COUNT;
    for (int i = 0; i < ITEM_COUNT; i++)
    {
        m_items[i].setSize({float(DisplayWidth) * ScreenFract, itemHeight});
        m_items[i].setPosition({float(DisplayWidth) * PositionFract, (float(DisplayHeight) * PositionFract) + (itemHeight * i)});
    }
}

void Store::update(float dt)
{
    m_timer += sf::seconds(dt);

    if (m_timer > sf::seconds(0.25))
    {
        if (Input.get()->isAction(Action::A_STORE))
        {
            m_isActive = !m_isActive;
            m_scene->setPause(m_isActive);

            m_items[ITEM_HEAL].enable();

            m_timer = sf::seconds(0);
        }
        if (Input.get()->isAction(Action::A_UP))
        {
            m_selected = std::max(0, --m_selected);
            m_timer = sf::seconds(0);
        }
        if (Input.get()->isAction(Action::A_DOWN))
        {
            m_selected = std::min(ITEM_COUNT - 1, ++m_selected);
            m_timer = sf::seconds(0);
        }
        if (Input.get()->isAction(Action::A_CONFIRM) && m_items[m_selected].isEnabled())
        {
			if (gamevars::PlayerMoney >= m_items[m_selected].getPrice())
			{
				m_items[m_selected].disable();

				gamevars::PlayerMoney -= m_items[m_selected].getPrice();
				m_scene->findObject<Hud>("hud")->setMoney(gamevars::PlayerMoney);

				switch (m_selected)
				{
					case ITEM_SHOTGUN:
						gamevars::WeaponUnlocked[ITEM_SHOTGUN + 1] = true;
						break;
					case ITEM_LASER:
						gamevars::WeaponUnlocked[ITEM_LASER + 1] = true;
						break;
					case ITEM_ROCKETS:
						gamevars::WeaponUnlocked[ITEM_ROCKETS + 1] = true;
						break;
					case ITEM_BRAKES:
                        gamevars::BrakeUnlocked = true;
						break;
                    case ITEM_HEAL:
                        m_scene->findObject<Player>("player_ship")->heal();
                        break;
				}
			}
            m_timer = sf::seconds(0);
        }
    }

    for (int i = 0; i < ITEM_COUNT; i++)
    {
        m_items[i].setSelected(i == m_selected);
    }
}

void Store::draw()
{
    if (m_isActive)
    {
        Renderer.draw(m_overlay);

        for (int i = 0; i < ITEM_COUNT; i++)
            m_items[i].draw();
    }
}

