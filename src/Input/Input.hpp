#pragma once
#include <SDL2/SDL.h>
#include "Core/Math.hpp"

class _Input
{
public:
    enum Button
    {
        BUTTON_A = SDL_CONTROLLER_BUTTON_A,
        BUTTON_B = SDL_CONTROLLER_BUTTON_B,
        BUTTON_X = SDL_CONTROLLER_BUTTON_X,
        BUTTON_Y = SDL_CONTROLLER_BUTTON_Y,
        BUTTON_SHARE = SDL_CONTROLLER_BUTTON_BACK,
        BUTTON_LOGO = SDL_CONTROLLER_BUTTON_GUIDE,
        BUTTON_MENU = SDL_CONTROLLER_BUTTON_START,
        BUTTON_LSTICK = SDL_CONTROLLER_BUTTON_LEFTSTICK,
        BUTTON_RSTICK = SDL_CONTROLLER_BUTTON_RIGHTSTICK,
        BUTTON_LSHOULDER = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
        BUTTON_RSHOULDER = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
        BUTTON_DPAD_UP = SDL_CONTROLLER_BUTTON_DPAD_UP,
        BUTTON_DPAD_DOWN = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
        BUTTON_DPAD_LEFT = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
        BUTTON_DPAD_RIGHT = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
        BUTTON_LTRIGGER,
        BUTTON_RTRIGGER
    };

    Input() = default;
    ~Input();

    void init();
    void update();

    bool isButton(Button button);

    void rumble(float strength, int duration);

    vec2 getLeftStick();
    vec2 getRightStick();

private:
    SDL_GameController* m_controller = nullptr;
    SDL_Haptic* m_haptic = nullptr;
};

//I ain't afraid of livin' on the edge
extern _Input Input;