#pragma once
#include "Enemy.hpp"
#include "Scene/UI/ProgressBar.hpp"
#include <SFML/System/Clock.hpp>

class Bully : public Enemy
{
public:
    Bully(Scene* scene);
    ~Bully() = default;

    void ready(const vec2& spawnPoint = vec2(0,0));

    void update(float dt) override final;

private:
    sf::Time m_clock;
    vec2 m_spawnPoint;
    SceneObject* m_client = nullptr;
};