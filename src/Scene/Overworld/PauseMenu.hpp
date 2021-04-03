#pragma once
#include "Scene/SceneObject.hpp"
#include "Scene/UI/Label.hpp"
#include "Scene/UI/ProgressBar.hpp"
#include <SFML/Graphics.hpp>
#include <functional>

class PauseMenu : public SceneObject
{
public:
    PauseMenu(Scene* scene);
    ~PauseMenu() = default;

    void update(float dt) override final;
    void draw() override final;

    void enable();

private:
    sf::RectangleShape m_overlay;
    sf::Font m_font;
    Label m_text;

    ProgressBar m_volumeBar;
    Label m_volumeText;

    sf::Time m_timer = sf::seconds(0);

    bool m_isActive = false;

    bool m_enabled = false;
};