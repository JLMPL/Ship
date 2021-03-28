#include "Input.hpp"
#include "Renderer.hpp"
#include "Core/Config.hpp"
#include <SFML/Window/Keyboard.hpp>

//hard choices arent' for me
//mixin' them SFML & SDL

InputLocator Input;

InputLocator::InputLocator()
{
    m_selected = &m_keyboardService;
}

void InputLocator::init()
{
    m_keyboardService.init();
    m_controllerService.init();

    m_font.loadFromFile("data/fonts/DejaVuSans.ttf");
    m_text.setFont(m_font);
    m_text.setCharacterSize(20);
}

void InputLocator::update()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
    {
        m_selected = &m_keyboardService;
        m_keyboardService.setCursorPosition(m_controllerService.getCursorPosition());
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
    {
        m_selected = &m_controllerService;
        m_selected->findDevice();
        m_controllerService.setCursorPosition(m_keyboardService.getCursorPosition());
    }

    m_selected->update();
}

void InputLocator::debugDraw()
{
    if (isController())
        m_text.setString("input: Controller");
    else
        m_text.setString("input: Keyboard & Mouse");

    m_text.setPosition({
        DisplayWidth - (m_text.getLocalBounds().width + 24),
        24.f
    });

    // Renderer.draw(m_text);
}

InputService* InputLocator::get()
{
    return m_selected;
}

bool InputLocator::isController() const
{
    return m_selected == &m_controllerService;
}