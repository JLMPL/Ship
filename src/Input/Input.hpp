#pragma once
#include "InputController.hpp"
#include "InputKeyboard.hpp"
#include "Core/Math.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class InputLocator
{
public:
    InputLocator();
    ~InputLocator() = default;

    void init();
    void update();
    void debugDraw();

    InputService* get();

    bool isController() const;

private:
    InputService* m_selected = nullptr;
    InputController m_controllerService;
    InputKeyboard m_keyboardService;

    sf::Font m_font;
    sf::Text m_text;
};

extern InputLocator Input;