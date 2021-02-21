#pragma once
#include "InputService.hpp"

class InputKeyboard : public InputService
{
public:
    InputKeyboard() = default;
    ~InputKeyboard() = default;

    void update() override final;

    bool isBaseWeapon() override final;
    bool isShotgun() override final;
    bool isLaser() override final;

    bool isConfirm() override final;

    bool isMenu() override final;
    bool isFire() override final;

    bool isStore() override final;

    vec2 getCursorPosition() override final;
    float getAcceleration() override final;

private:
};