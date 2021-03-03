#include "Store.hpp"
#include "Renderer.hpp"
#include "Core/Config.hpp"
#include "Input/Input.hpp"
#include "Scene/Scene.hpp"

/*
To buy
Shotgun
Laser
Rockets
Brake
*/

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

    int itemHeight = (DisplayHeight * ScreenFract) / NumItems;
    for (int i = 0; i < 4; i++)
    {
        m_items[i].setSize({DisplayWidth * ScreenFract, itemHeight});
        m_items[i].setPosition({DisplayWidth * PositionFract, (DisplayHeight * PositionFract) + (itemHeight * i)});
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
            m_timer = sf::seconds(0);
        }
        if (Input.get()->isAction(Action::A_UP))
        {
            m_selected = std::max(0, --m_selected);
            m_timer = sf::seconds(0);
        }
        if (Input.get()->isAction(Action::A_DOWN))
        {
            m_selected = std::min(NumItems - 1, ++m_selected);
            m_timer = sf::seconds(0);
        }
        if (Input.get()->isAction(Action::A_CONFIRM))
        {
            m_items[m_selected].disable();
            m_timer = sf::seconds(0);
        }
    }

    for (int i = 0; i < 4; i++)
    {
        m_items[i].setSelected(i == m_selected);
    }
}

void Store::draw()
{
    if (m_isActive)
    {
        Renderer.draw(m_overlay);

        for (int i = 0; i < 4; i++)
            m_items[i].draw();
    }
}

