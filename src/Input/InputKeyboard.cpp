#include "InputKeyboard.hpp"
#include "Renderer.hpp"
#include "Core/Config.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SDL2/SDL.h>

void InputKeyboard::update()
{
    vec2 mp = Renderer::get().getLocalMousePosition();
    vec2 diff = mp - vec2(200,200);

    m_cursor += diff * 0.01f;

    Renderer::get().setLocalMousePosition({200,200});
}

bool InputKeyboard::isBaseWeapon()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Num1);
}

bool InputKeyboard::isShotgun()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Num2);
}

bool InputKeyboard::isLaser()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Num3);
}

bool InputKeyboard::isMenu()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
}

bool InputKeyboard::isFire()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
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
