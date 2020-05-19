#pragma once
#include "Layer.hpp"
#include "Physics/PhysicsWorld.hpp"
#include <SFML/Graphics.hpp>

class GameLayer : public Layer
{
public:
    GameLayer(LayerStack& ss);
    ~GameLayer() = default;

    void update(float dt) override final;
    void draw() override final;

private:
    std::array<sf::Vertex, 5> m_ship;

    PhysicsWorld m_physWorld;
};