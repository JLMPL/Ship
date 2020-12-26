#include "Menu.hpp"
#include "Renderer.hpp"

Menu::Menu(Scene* scene)
 : SceneObject(scene)
{
    m_font.loadFromFile("data/NotoSans-Regular.ttf");
    m_timer.restart();
}

void Menu::addItem(const std::string& name, std::function<void (void)>&& callback, bool active)
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

void Menu::update(float dt)
{
    m_prevButtons[0] = m_buttons[0];
    m_prevButtons[1] = m_buttons[1];
    m_prevButtons[2] = m_buttons[2];

    if (m_timer.getElapsedTime().asMilliseconds() > 250)
    {
        m_buttons[0] = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        m_buttons[1] = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
        m_buttons[2] = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);
    }

    if (m_buttons[0] && !m_prevButtons[0])
    {
        m_selection = std::max(m_selection - 1, 0);
        if (!m_items[m_selection].active)
            m_selection++;
    }

    if (m_buttons[1] && !m_prevButtons[1])
        m_selection = std::min(m_selection + 1, int(m_items.size()) - 1);

    if (m_buttons[2] && !m_prevButtons[2])
        m_items[m_selection].callback();

    for (uint i = 0; i < m_items.size(); i++)
    {
        if (i == m_selection)
            m_items[i].text.setFillColor(sf::Color::White);
        else
            m_items[i].text.setFillColor({128,128,128,255});

        if (!m_items[i].active)
            m_items[i].text.setFillColor({64,64,64,255});
    }
}

void Menu::draw()
{
    float i = 0;
    for (auto& item : m_items)
    {
        item.text.setPosition({32, 300 + i});
        Renderer::get().draw(item.text);
        i += 48;
    }
}
