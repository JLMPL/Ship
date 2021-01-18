#pragma once
#include "SceneObject.hpp"
#include "UI/Label.hpp"
#include <SFML/Graphics/Rect.hpp>

enum TutorialType
{
    TUTORIAL_HEALTH,
    TUTORIAL_OBJECTIVE,
    TUTORIAL_XP
};

class Tutorial : public SceneObject
{
public:
    Tutorial(Scene* scene);
    ~Tutorial() = default;

    void update(float dt) override final;
    void draw() override final;

    void show(TutorialType tut);

private:
    sf::FloatRect m_highlight;
    sf::Font m_font;
    Label m_text;
    bool m_visible = false;
};