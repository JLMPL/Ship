#pragma once
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>

class Menu
{
public:
    struct Item
    {
        std::string name = "[name]";
        std::function<void (void)> callback;
        bool active = true;

        sf::Text text;
    };

    Menu();

    void addItem(const std::string& name, std::function<void (void)>&& callback, bool active = true);

    void update(float dt);
    void draw();

private:
    std::vector<Item> m_items;

    sf::Font m_font;
    int m_selection = 99;

    bool m_buttons[3] = {false};
    bool m_prevButtons[3] = {false};

    sf::Clock m_timer;
};