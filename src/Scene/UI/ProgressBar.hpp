#pragma once
#include "Core/Math.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

class ProgressBar
{
public:
    ProgressBar();

    void draw();

    void setValue(int value);
    void setMaxValue(int value);
    void setColor(const sf::Color& color);

    void setPosition(const vec2& pos);
    void setOffset(const vec2& offset);

private:
    sf::RectangleShape m_back;
    sf::RectangleShape m_front;

    int m_maxValue = 100;
    int m_value = 50;

    vec2 m_offset;
};