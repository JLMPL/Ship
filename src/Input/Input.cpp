#include "Input.hpp"

_Input Input;

Input::~Input()
{
    SDL_HapticClose(0);
    SDL_GameControllerClose(0);
    SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
    SDL_QuitSubSystem(SDL_INIT_HAPTIC);
}

void Input::init()
{
    SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);
    SDL_InitSubSystem(SDL_INIT_HAPTIC);

    for (int i = 0; i < SDL_NumJoysticks(); ++i)
    {
        if (SDL_IsGameController(i))
        {
            printf("GameController found at slot %i.\n", i);
        }
    }

    m_controller = SDL_GameControllerOpen(0);
    m_haptic = SDL_HapticOpen(0);
    SDL_HapticRumbleInit(m_haptic);
}

void Input::update()
{
    SDL_GameControllerUpdate();
}

bool Input::isButton(Button button)
{
    if (button == BUTTON_LTRIGGER)
    {
        return SDL_GameControllerGetAxis(m_controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT) > 16384;
    }
    else if (button == BUTTON_RTRIGGER)
    {
        return SDL_GameControllerGetAxis(m_controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > 16384;
    }
    else
        return SDL_GameControllerGetButton(m_controller, (SDL_GameControllerButton)button);
}

void Input::rumble(float strength, int duration)
{
    SDL_HapticRumblePlay(m_haptic, strength, duration);
}

vec2 Input::getLeftStick()
{
    return {
        float(SDL_GameControllerGetAxis(m_controller, SDL_CONTROLLER_AXIS_LEFTX)) / 32768.f,
        float(SDL_GameControllerGetAxis(m_controller, SDL_CONTROLLER_AXIS_LEFTY)) / 32768.f
    };
}

vec2 Input::getRightStick()
{
    return {
        float(SDL_GameControllerGetAxis(m_controller, SDL_CONTROLLER_AXIS_RIGHTX)) / 32768.f,
        float(SDL_GameControllerGetAxis(m_controller, SDL_CONTROLLER_AXIS_RIGHTY)) / 32768.f
    };
}
