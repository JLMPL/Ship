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
    {
        printf("Contact %d\n", *userDataA);
        event.receiver = *userDataA;
    }
    if (userDataB)
    {
        printf("Contact %d\n", *userDataB);
        event.receiver = *userDataB;
    }

    EventQueue::get().pushEvent(event);
}
