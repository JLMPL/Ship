#pragma once
#include "Scene/SceneObject.hpp"
#include "Scene/UI/Label.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

class Cutscene : public SceneObject
{
public:
    Cutscene(Scene* scene);
    ~Cutscene() = default;

    void ready();
    void update(float dt) override final;
    void draw() override final;

private:
    sf::RectangleShape m_overlay;

    int m_index = 0;
    float m_alpha = 0;

    sf::Font m_font;
    std::vector<Label> m_lines;

    Label m_skip;
};