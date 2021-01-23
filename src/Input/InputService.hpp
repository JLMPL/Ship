#pragma once
#include "Core/Math.hpp"

class InputService
{
public:
    InputService() = default;
    virtual ~InputService() = default;

    virtual void init() {}
    virtual void findDevice() {}
    virtual void update() {}

    virtual void rumble(float strength, int milliseconds) {}

    virtual bool isBaseWeapon() = 0;
    virtual bool isShotgun() = 0;
    virtual bool isLaser() = 0;

    virtual bool isMenu() = 0;
    virtual bool isFire() = 0;
    virtual bool isConfirm() = 0;

    virtual void setCursorPosition(const vec2& pos)
        {m_cursor = pos;}
    virtual vec2 getCursorPosition() = 0;
    virtual float getAcceleration() = 0;

protected:
    vec2 m_cursor;

};