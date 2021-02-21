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

static constexpr float ScreenFract = 0.5;
static constexpr float PositionFract = (1.f - ScreenFract) / 2.f;

Store::Store(Scene* scene)
 : SceneObject(scene)
{
    m_name = "Store";
    m_pausable = false;

    m_overlay.setSize({DisplayWidth * ScreenFract, DisplayHeight * ScreenFract});
    m_overlay.setPosition({DisplayWidth * PositionFract, DisplayHeight * PositionFract});
    m_overlay.setFillColor(sf::Color(0,0,0,192));

    m_items[0].setData(L"Blaster Spread", L"Shoots a wide cone of bolts covering a large area.\nVery effective at short distance.", 1520);
    m_items[1].setData(L"Laser", L"Deals continous damage in a straight line.\nEffective at a long distance.", 3210);
    m_items[2].setData(L"Homing Rockets", L"Rockets automatically homing towards closest enemies.\nEffective against groups.", 5560);
    m_items[3].setData(L"Ultra Brakes", L"Stops any and all momentum on the ship. Huge power cost.", 2310);

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

    if (m_timer > sf::seconds(0.25) && Input.get()->isStore())
    {
        m_isActive = !m_isActive;
        m_scene->setPause(m_isActive);
        m_timer = sf::seconds(0);
    }
}

void Store::draw()
{
    if (m_isActive)
    {
        Renderer::get().draw(m_overlay);

        for (int i = 0; i < 4; i++)
            m_items[i].draw();
    }
}

