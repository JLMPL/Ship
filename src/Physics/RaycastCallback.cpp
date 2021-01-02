#include "RaycastCallback.hpp"

float RaycastCallback::ReportFixture(
    b2Fixture *fix,
    const b2Vec2 &p,
    const b2Vec2 &n,
    float f)
{
    object = (SceneObject*)fix->GetBody()->GetUserData();
    point = {p.x, p.y};
    normal = {n.x, n.y};
    fraction = f;

    hasHit = true;

    return 0;
}