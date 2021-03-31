#pragma once
#include "Enemy.hpp"
#include <SFML/System/Clock.hpp>

class Kamikaze : public Enemy
{
public:
    Kamikaze(Scene* scene);
    ~Kamikaze() = default;

    void ready(const vec2& spawnPoint = vec2(0,0));

    void update(float dt) override final;

    void onContact(SceneObject* other) override final;

private:
    vec2 m_spawnPoint;
};