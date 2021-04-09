#pragma once
#include "Enemy.hpp"
#include "Scene/UI/ProgressBar.hpp"

class Client : public Enemy
{
public:
    Client(Scene* scene);
    ~Client() = default;

    void ready(const vec2& spawnPoint = vec2(0,0));

    void update(float dt) override final;

private:
    vec2 m_spawnPoint;
};