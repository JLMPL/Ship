#include "ProgressBar.hpp"
#include "Renderer.hpp"

ProgressBar::ProgressBar()
{
    m_back.setSize({2,0.15});
    m_back.setFillColor(sf::Color::Black);

    m_front.setSize({2,0.15});
    m_front.setFillColor({192,192,192});
}

void ProgressBar::draw()
{
    float scale = float(m_value) / float(m_maxValue);

    m_front.setScale({scale, 1});

    if (m_isScaled)
    {
        Renderer.drawScaled(m_back);
        Renderer.drawScaled(m_front);
    }
    else
    {
        Renderer.draw(m_back);
        Renderer.draw(m_front);
    }
}

void ProgressBar::setValue(int value)
{
    m_value = value;
}

void ProgressBar::setMaxValue(int value)
{
    m_maxValue = value;
    // setValue(m_maxValue);
}

void ProgressBar::setColor(const sf::Color& color)
{
    m_front.setFillColor(color);
}

void ProgressBar::setPosition(const vec2& pos)
{
    vec2 drop = (m_isScaled) ? vec2(0,0) : vec2(3,3);

    m_back.setPosition(pos + m_offset + drop);
    m_front.setPosition(pos + m_offset);
}

void ProgressBar::setOffset(const vec2& offset)
{
    m_offset = offset;
}

void ProgressBar::setSize(const vec2& size)
{
    m_back.setSize({size.x,size.y});
    m_front.setSize({size.x,size.y});
}

vec2 ProgressBar::getSize() const
{
    return {m_back.getLocalBounds().width, m_back.getLocalBounds().height};
}

void ProgressBar::setScaled(bool value)
{
    m_isScaled = value;
}

void ProgressBar::setOutline(bool value)
{
    m_back.setOutlineThickness(value);
    m_back.setOutlineColor(m_front.getFillColor());
}