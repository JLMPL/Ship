#include "RaycastCallback.hpp"

float RaycastCallback::ReportFixture(
    b2Fixture *fixture,
    const b2Vec2 &p,
    const b2Vec2 &n,
    float f)
{
    point = {p.x, p.y};
    normal = {n.x, n.y};
    fraction = f;

    hasHit = true;

    return 0;
}