#pragma once
#include "SceneObject.hpp"
#include "Core/Types.hpp"
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>
#include "Visual/Mesh.hpp"
#include "Scene/UI/Label.hpp"

class Menu : public SceneObject
{
public:
    struct Item
    {
        std::wstring name = L"[name]";
        std::function<void (void)> callback;
        bool active = true;

        Label text;
    };

    Menu(Scene* scene);

    void addItem(const std::wstring& name, std::function<void (void)>&& callback, bool active = true);
    void setCaption(int index, const std::wstring& name);

    void update(float dt);
    void draw();

private:
    std::vector<Item> m_items;

    sf::Font m_font;
    int m_selection = 99;

    bool m_buttons[3] = {false};
    bool m_prevButtons[3] = {false};

    sf::Clock m_timer;
    Mesh m_mesh;

    float m_angle = 0.f;
};