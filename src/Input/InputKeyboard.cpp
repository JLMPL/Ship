#include "InputKeyboard.hpp"
#include "Renderer.hpp"
#include "Core/Config.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SDL2/SDL.h>

InputKeyboard::InputKeyboard()
{
    m_bindings[A_BASE_WEAPON] = sf::Keyboard::Num1;
    m_bindings[A_SHOTGUN] = sf::Keyboard::Num2;
    m_bindings[A_LASER] = sf::Keyboard::Num3;
    m_bindings[A_MENU] = sf::Keyboard::Escape;
    m_bindings[A_CONFIRM] = sf::Keyboard::Return;
    m_bindings[A_STORE] = sf::Keyboard::Tab;
    m_bindings[A_UP] = sf::Keyboard::Up;
    m_bindings[A_DOWN] = sf::Keyboard::Down;
    m_bindings[A_LEFT] = sf::Keyboard::Left;
    m_bindings[A_RIGHT] = sf::Keyboard::Right;
}

void InputKeyboard::update()
{
    vec2 mp = Renderer.getLocalMousePosition();
    vec2 diff = mp - vec2(200,200);

    m_cursor += diff * 0.01f;

    Renderer.setLocalMousePosition({200,200});
}

bool InputKeyboard::isAction(Action act)
{
    if (act == Action::A_FIRE)
        return sf::Mouse::isButtonPressed(sf::Mouse::Left);
    else
        return sf::Keyboard::isKeyPressed(m_bindings[act]);
}

vec2 InputKeyboard::getCursorPosition()
{
    return m_cursor;
}

float InputKeyboard::getAcceleration()
{
    float acceleration = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) and
        sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        acceleration = 1.f;
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        acceleration = 0.5f;
    }

    return acceleration;
}
