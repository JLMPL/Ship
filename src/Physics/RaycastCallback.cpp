#include "RaycastCallback.hpp"

float RaycastCallback::ReportFixture(
    b2Fixture *fixture,
    const b2Vec2 &point,
    const b2Vec2 &normal,
    float fraction)
{
    m_point = {point.x, point.y};
    m_normal = {normal.x, normal.y};
    m_fraction = fraction;

    m_hasHit = true;

    return 0;
}