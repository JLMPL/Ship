#pragma once
#include "InputController.hpp"
#include "InputKeyboard.hpp"
#include "Core/Math.hpp"

class InputLocator
{
public:
    InputLocator();
    ~InputLocator() = default;

    void init();
    void update();

    InputService* get();

private:
    InputService* m_selected = nullptr;
    InputController m_controllerService;
    InputKeyboard m_keyboardService;
};

//I ain't afraid of livin' on the edge
extern InputLocator Input;