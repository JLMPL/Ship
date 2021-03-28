#pragma once
#include "Scene/SceneObject.hpp"
#include "Scene/UI/ProgressBar.hpp"
#include "Scene/UI/Label.hpp"
#include "Visual/Mesh.hpp"
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
    void setWeapon(int weapon);
    void setMoney(int value);
    void setShowOutOfBounds(bool value);

private:
    ProgressBar m_heatBar;
    ProgressBar m_hpBar;

    sf::Font m_font;

    Label m_overheatText;
    bool m_overheat = false;

    Label m_weaponName;

    float m_heat = 0.f;
    float m_healthPercentage = 1.f;

    Label m_money;
	Mesh m_wheel[4];
	Mesh m_wheelShadow[4];

    Label m_outOfBounds;
    bool m_isOutOfBounds = false;
};