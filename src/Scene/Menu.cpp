#include "Menu.hpp"
#include "Renderer.hpp"
#include "Core/Config.hpp"
#include "Audio/Audio.hpp"
#include "Input/Input.hpp"
#include <cmath>

Menu::Menu(Scene* scene)
 : SceneObject(scene)
{
    m_font.loadFromFile("data/fonts/NotoSans-Regular.ttf");
    m_timer.restart();
    m_mesh.loadFromFile("data/meshes/select_arrow.obj");
    m_mesh.setScale(10.f);
}

void Menu::addItem(const std::wstring& name, std::function<void (void)>&& callback, bool active)
{
    m_items.push_back(Item());
    Item& item = m_items.back();

    item.name = name;
    item.callback = callback;
    item.active = active;
    item.text.setFont(m_font);
    item.text.setCharacterSize(32);
    item.text.setString(item.name);

    if (item.active && m_items.size() - 1 < m_selection)
    {
        m_selection = m_items.size() - 1;
    }
}

void Menu::setCaption(int index, const std::wstring& name)
{
    m_items[index].name = name;
    m_items[index].text.setString(name);
}

void Menu::update(float dt)
{
    m_prevButtons[0] = m_buttons[0];
    m_prevButtons[1] = m_buttons[1];
    m_prevButtons[2] = m_buttons[2];

    if (m_timer.getElapsedTime().asMilliseconds() > 250)
    {
        m_buttons[0] = Input.get()->isAction(Action::A_UP);
        m_buttons[1] = Input.get()->isAction(Action::A_DOWN);
        m_buttons[2] = Input.get()->isAction(Action::A_CONFIRM);
    }

    if (m_buttons[0] && !m_prevButtons[0])
    {
        m_selection = std::max(m_selection - 1, 0);
        if (!m_items[m_selection].active)
            m_selection++;

        Audio.playSound(_Audio::EFFECT_MENU_SWITCH);
    }

    if (m_buttons[1] && !m_prevButtons[1])
    {
        m_selection = std::min(m_selection + 1, int(m_items.size()) - 1);
        Audio.playSound(_Audio::EFFECT_MENU_SWITCH);
    }

    if (m_buttons[2] && !m_prevButtons[2])
    {
        m_items[m_selection].callback();
        Audio.playSound(_Audio::EFFECT_MENU_SELECT);
    }

    // for (uint i = 0; i < m_items.size(); i++)
    // {
    //     if (i == m_selection)
    //         m_items[i].text.setFillColor(sf::Color::White);
    //     else
    //         m_items[i].text.setFillColor({128,128,128,255});

    //     if (!m_items[i].active)
    //         m_items[i].text.setFillColor({64,64,64,255});
    // }

    m_angle += dt * 2;
    m_mesh.setScale({10.f, cos(m_angle) * 15.f});
}

void Menu::draw()
{
    int ind = 0;
    float i = 0;
    for (auto& item : m_items)
    {
        item.text.setPosition({64, (DisplayHeight/2) + i});
        item.text.draw();

        if (ind == m_selection)
            m_mesh.setPosition({55, (DisplayHeight/2) + i + 20});

        i += 48;
        ind++;
    }

    m_mesh.draw(false);
}
