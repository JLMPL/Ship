#include "InputController.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "Core/Timer.hpp"

//hard choices arent' for me
//mixin' them SFML & SDL

InputController::InputController()
{
    m_bindings[A_BASE_WEAPON] = BUTTON_DPAD_DOWN;
    m_bindings[A_SHOTGUN] = BUTTON_DPAD_RIGHT;
    m_bindings[A_LASER] = BUTTON_DPAD_UP;
    m_bindings[A_MENU] = BUTTON_MENU;
    m_bindings[A_FIRE] = BUTTON_RSHOULDER;
    m_bindings[A_CONFIRM] = BUTTON_A;
    m_bindings[A_STORE] = BUTTON_Y;
    m_bindings[A_UP] = BUTTON_DPAD_UP;
    m_bindings[A_DOWN] = BUTTON_DPAD_DOWN;
    m_bindings[A_LEFT] = BUTTON_DPAD_LEFT;
    m_bindings[A_RIGHT] = BUTTON_DPAD_RIGHT;
}

InputController::~InputController()
{
    SDL_HapticClose(m_haptic);
    SDL_GameControllerClose(m_controller);
    SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
    SDL_QuitSubSystem(SDL_INIT_HAPTIC);
}

void InputController::init()
{
    SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);
    SDL_InitSubSystem(SDL_INIT_HAPTIC);
}

void InputController::findDevice()
{
    for (int i = 0; i < SDL_NumJoysticks(); ++i)
    {
        if (SDL_IsGameController(i))
        {
            //printf("GameController found at slot %i.\n", i);
            m_controllerSlot = i;
            break;
        }
    }

    SDL_HapticClose(m_haptic);
    SDL_GameControllerClose(m_controller);
    m_controller = SDL_GameControllerOpen(m_controllerSlot);
    m_haptic = SDL_HapticOpen(m_controllerSlot);
    SDL_HapticRumbleInit(m_haptic);
}

void InputController::update()
{
    SDL_GameControllerUpdate();

    m_cursor += getLeftStick() * 20.f * timer::delta;
}

bool InputController::isButton(Button button)
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

void InputController::rumble(float strength, int duration)
{
    SDL_HapticRumblePlay(m_haptic, strength, duration);
}

vec2 InputController::getLeftStick()
{
    return {
        float(SDL_GameControllerGetAxis(m_controller, SDL_CONTROLLER_AXIS_LEFTX)) / 32768.f,
        float(SDL_GameControllerGetAxis(m_controller, SDL_CONTROLLER_AXIS_LEFTY)) / 32768.f
    };
}

vec2 InputController::getRightStick()
{
    return {
        float(SDL_GameControllerGetAxis(m_controller, SDL_CONTROLLER_AXIS_RIGHTX)) / 32768.f,
        float(SDL_GameControllerGetAxis(m_controller, SDL_CONTROLLER_AXIS_RIGHTY)) / 32768.f
    };
}

bool InputController::isAction(Action act)
{
    return isButton(m_bindings[act]);
}

vec2 InputController::getCursorPosition()
{
    return m_cursor;
}

float InputController::getAcceleration()
{
    return (float(SDL_GameControllerGetAxis(m_controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT)) / 32768.f);
}
