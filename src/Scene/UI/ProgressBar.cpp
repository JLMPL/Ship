#include "ProgressBar.hpp"
#include "Renderer.hpp"

ProgressBar::ProgressBar()
{
    m_back.setSize({4,0.3});
    m_back.setFillColor(sf::Color::Black);

    m_front.setSize({4,0.3});
    m_front.setFillColor(sf::Color::Red);
}

void ProgressBar::draw()
{
    float scale = float(m_value) / float(m_maxValue);

    m_front.setScale({scale, 1});

    Renderer::get().drawScaled(m_back);
    Renderer::get().drawScaled(m_front);
}

void ProgressBar::setValue(int value)
{
    m_value = value;
}

void ProgressBar::setMaxValue(int value)
{
    m_maxValue = value;
    setValue(m_maxValue);
}

void ProgressBar::setColor(const sf::Color& color)
{
    m_front.setFillColor(color);
    m_back.setOutlineColor(color);
}

void ProgressBar::setPosition(const vec2& pos)
{
    m_back.setPosition(pos + m_offset);
    m_front.setPosition(pos + m_offset);
}

void ProgressBar::setOffset(const vec2& offset)
{
    m_offset = offset;
}
