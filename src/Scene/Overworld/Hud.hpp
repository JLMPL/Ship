#pragma once
#include "Scene/SceneObject.hpp"
#include "Scene/UI/ProgressBar.hpp"
#include <SFML/Graphics.hpp>
#include <functional>

class Hud : public SceneObject
{
public:
    Hud(Scene* scene);
    ~Hud() = default;

    void update(float dt) override final;
    void draw() override final;

    void setHeat(float level);
    void setHealthPercentage(float perc);
    void setPlayerCoords(int x, int y);
    void setWeapon(int weapon);
    void setXp(int value, int max);

private:
    sf::RectangleShape m_heatBack;
    sf::RectangleShape m_heatRect;
    sf::RectangleShape m_hpBack;
    sf::RectangleShape m_hp;

    sf::Font m_font;

    sf::Text m_overheatText;
    bool m_overheat = false;

    float m_heat = 0.f;
    float m_healthPercentage = 1.f;
    vec2i m_playerCoords = {0,0};

    sf::Text m_coords;

    sf::Texture m_weaponsTex;
    sf::Sprite m_weapons[4];

    ProgressBar m_xpBar;
    sf::Text m_xpText;
};