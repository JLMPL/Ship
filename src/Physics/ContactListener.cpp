#include "ContactListener.hpp"
#include "Scene/SceneObject.hpp"
#include <cstdio>

void ContactListener::BeginContact(b2Contact *contact)
{
    SceneObject* userDataA = (SceneObject*)contact->GetFixtureA()->GetBody()->GetUserData();
    SceneObject* userDataB = (SceneObject*)contact->GetFixtureB()->GetBody()->GetUserData();

    if (userDataA)
        userDataA->onContact(userDataB);

    if (userDataB)
        userDataB->onContact(userDataA);
}
