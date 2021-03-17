#pragma once
#include "Spacecraft.hpp"
#include "Scene/UI/ProgressBar.hpp"

class Enemy : public Spacecraft
{
public:
    Enemy(Scene* scene);
    ~Enemy() = default;

    virtual void onContact(SceneObject* other) override;
    virtual void damage(int value) override;

    virtual void draw() override;

protected:
    SceneObject* m_player = nullptr;
    bool m_isDead = false;

    ProgressBar m_healthbar;

    int m_moneyValue = 1;
};