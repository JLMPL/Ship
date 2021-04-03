#pragma once
#include "Scene/SceneObject.hpp"
#include "Scene/UI/Label.hpp"
#include <SFML/Graphics.hpp>

class GameOver : public SceneObject
{
public:
    GameOver(Scene* scene);
    ~GameOver() = default;

    void update(float dt) override final;
    void draw() override final;

    void show();

private:
    sf::RectangleShape m_overlay;
    sf::Font m_font;
    Label m_text;
    Label m_smol;
    Label m_skip;

    sf::Time m_timer = sf::seconds(0);

    float m_alpha = 0.f;
    float m_textAlpha = 0.f;

    bool m_isActive = false;
};