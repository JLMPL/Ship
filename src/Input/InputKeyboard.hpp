#pragma once
#include "InputService.hpp"
#include <SFML/Window/Keyboard.hpp>

class InputKeyboard : public InputService
{
public:
    InputKeyboard();
    ~InputKeyboard() = default;

    void update() override final;

    bool isAction(Action act) override final;

    vec2 getCursorPosition() override final;
    float getAcceleration() override final;

private:
    sf::Keyboard::Key m_bindings[Action::A_COUNT];
};