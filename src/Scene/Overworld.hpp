#pragma once
#include "Scene.hpp"

class Overworld : public Scene
{
public:
    Overworld(Game* game);
    ~Overworld() = default;

    // void ready() override final;
    // void update(float dt) override final;
    // void draw() override final;

private:
    std::vector<StaticBody::Ref> m_planets;
};