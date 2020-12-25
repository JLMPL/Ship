#pragma once
#include "Libs/box2d/box2d.h"
#include "Core/Math.hpp"

class RaycastCallback : public b2RayCastCallback
{
public:
    float ReportFixture(
        b2Fixture *fixture,
        const b2Vec2 &point,
        const b2Vec2 &normal,
        float fraction) override final;

public:
    sf::Vector2f point;
    sf::Vector2f normal;
    float fraction;
    bool hasHit = false;
};