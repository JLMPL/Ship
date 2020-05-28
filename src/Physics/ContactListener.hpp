#pragma once
#include "Libs/box2d/box2d.h"

class ContactListener : public b2ContactListener
{
public:
    void BeginContact(b2Contact *contact) override final;

private:

};