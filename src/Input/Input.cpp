#include "Input.hpp"
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

InputService* InputLocator::get()
{
    return m_selected;
}