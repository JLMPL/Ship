#include "ContactListener.hpp"
#include "Events/EventQueue.hpp"
#include <cstdio>

void ContactListener::BeginContact(b2Contact *contact)
{
    int* userDataA = (int*)contact->GetFixtureA()->GetBody()->GetUserData();
    int* userDataB = (int*)contact->GetFixtureB()->GetBody()->GetUserData();

    if (userDataA)
    {
        Event kill;
        kill.type = Event::DamageEntity;
        kill.receiver = *userDataA;
        EventQueue::get().pushEvent(kill);
    }
    if (userDataB)
    {
        Event kill;
        kill.type = Event::DamageEntity;
        kill.receiver = *userDataB;
        EventQueue::get().pushEvent(kill);
    }

}
