#pragma once
#include "Layer.hpp"
#include <SFML/Graphics.hpp>
#include "Physics/DebugDrawer.hpp"

class GameLayer : public Layer
{
public:
    GameLayer(LayerStack& ss);
    ~GameLayer() = default;

    void update(float dt) override final;
    void draw() override final;

private:
    std::array<sf::Vertex, 5> m_ship;

    b2World m_pWorld;
    b2Body* m_groundBody = nullptr;
    b2Body* m_body = nullptr;
    b2PolygonShape m_dynamicBox;

    DebugDrawer m_pDrawer;
};