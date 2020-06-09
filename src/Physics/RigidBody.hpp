
#pragma once
#include "Libs/box2d/box2d.h"
#include "Core/Math.hpp"
#include <memory>

class RigidBody

{
public:
    using Ptr = std::unique_ptr<RigidBody>;

    enum Type
    {
        PlayerShip = 0,
        EnemyShip,
        PlayerBullet,
        EnemyBullet,

        Count
    };

    RigidBody(b2Body* bd, b2World* world, Type type);
    ~RigidBody();

    void applyTorque(float torq);
    void applyLinearImpulse(const vec2& impulse);

    void rotateTowards(const vec2& target, float speed);

    vec2 getPosition() const;
    vec2 getDirection() const;
    float getAngle() const;

    void setUserData(int* id);
    int getUserData() const;

    const Type& getType() const;

private:
    Type m_type = Type::Count;

    b2Body* m_body = nullptr;
    b2World* m_world = nullptr;
};