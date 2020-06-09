#include "ContactListener.hpp"
#include "Events/EventQueue.hpp"
#include <cstdio>

void ContactListener::BeginContact(b2Contact *contact)
{
    int* userDataA = (int*)contact->GetFixtureA()->GetBody()->GetUserData();
    int* userDataB = (int*)contact->GetFixtureB()->GetBody()->GetUserData();

    Event event;
    event.type = Event::DestroyEntity;

    if (userDataA)
        event.receiver = *userDataA;
    if (userDataB)
        event.receiver = *userDataB;

    EventQueue::get().pushEvent(event);
}
