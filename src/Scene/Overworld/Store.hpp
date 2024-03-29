#pragma once
#include "Scene/SceneObject.hpp"
#include "StoreItem.hpp"
#include <SFML/Graphics.hpp>

class Store : public SceneObject
{
public:
	enum
	{
		ITEM_SHOTGUN = 0,
		ITEM_LASER,
		ITEM_ROCKETS,
		ITEM_BRAKES,
        ITEM_HEAL,
		ITEM_COUNT
	};

    Store(Scene* scene);
    ~Store() = default;

    void update(float dt) override final;
    void draw() override final;

private:
    sf::RectangleShape m_overlay;
    sf::Font m_font;
    Label m_text;

    sf::Time m_timer;

    StoreItem m_items[ITEM_COUNT];
    int m_selected = 0;

    bool m_isActive = false;
};