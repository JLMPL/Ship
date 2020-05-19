#include "GameLayer.hpp"
#include "LayerStack.hpp"
#include "Renderer.hpp"

GameLayer::GameLayer(LayerStack& layerStack)
    : Layer(layerStack), m_pWorld({0.f, 1.f})
{
    m_ship[0].position = {0,0};
    m_ship[1].position = {-10,48};
    m_ship[2].position = {0,32};
    m_ship[3].position = {10,48};
    m_ship[4].position = {0,0};

    m_pDrawer.SetFlags(b2Draw::e_shapeBit);
    m_pWorld.SetDebugDraw(&m_pDrawer);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 10.0f);
    m_groundBody = m_pWorld.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 1.0f);
    m_groundBody->CreateFixture(&groundBox, 0.0f);


    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(4.0f, 4.0f);
    m_body = m_pWorld.CreateBody(&bodyDef);

    m_dynamicBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &m_dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    m_body->CreateFixture(&fixtureDef);
}

void GameLayer::update(float dt)
{
    m_pWorld.Step(1.f/60.f, 6, 2);
}

void GameLayer::draw()
{
    m_pWorld.DebugDraw();

    sf::Transform tr;
    tr.translate({200,200}).rotate(45);

    sf::RenderStates rs(tr);

    Renderer::Get().draw(&m_ship[0], m_ship.size(), sf::LineStrip, rs);
}

