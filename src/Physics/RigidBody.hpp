#pragma once
#include "Libs/box2d/box2d.h"
#include "Core/Math.hpp"
#include <memory>

class RigidBody
{
public:
    using Ptr = std::unique_ptr<RigidBody>;
    using Ref = std::shared_ptr<RigidBody>;

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

    void fullStop();

    void rotateTowards(const vec2& target, float speed);

    void setPosition(const vec2& pos);

    vec2 getPosition() const;
    vec2 getDirection() const;
    vec2 getLinearVelocity() const;
    float getAngle() const;

    void setUserData(void* id);
    void* getUserData() const;

    const Type& getType() const;

private:
    Type m_type = Type::Count;

    b2Body* m_body = nullptr;
    b2World* m_world = nullptr;
};