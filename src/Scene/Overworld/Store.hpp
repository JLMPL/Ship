#pragma once
#include "Scene/SceneObject.hpp"
// #include "Scene/UI/Label.hpp"
#include "StoreItem.hpp"
#include <SFML/Graphics.hpp>

class Store : public SceneObject
{
public:
    static constexpr int NumItems = 4;

    Store(Scene* scene);
    ~Store() = default;

    void update(float dt) override final;
    void draw() override final;

private:
    sf::RectangleShape m_overlay;
    sf::Font m_font;
    Label m_text;

    sf::Time m_timer;

    StoreItem m_items[NumItems];
    int m_selected = 0;

    bool m_isActive = false;
};