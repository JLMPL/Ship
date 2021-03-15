#pragma once
#include "Scene/SceneObject.hpp"
#include "Physics/RigidBody.hpp"
#include <SFML/System/Clock.hpp>
#include "Visual/Trail.hpp"

class Bullet : public SceneObject
{
public:
    Bullet(Scene* scene);
    ~Bullet() = default;

    void ready(const vec2& pos, const vec2& dir, int damage = 10, bool player = false);
    void update(float dt) override final;
    void draw() override final;

    void onContact(SceneObject* other) override final;

    int getDamage() const;
    void setColor(const sf::Color& color);

private:
    RigidBody::Ref m_body = nullptr;
    sf::Time m_clock;

    int m_damage = 1;
    Trail m_trail;
    bool m_enabled = true;
};