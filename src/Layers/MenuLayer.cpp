#include "MenuLayer.hpp"
#include "LayerStack.hpp"
#include "Renderer.hpp"

MenuLayer::MenuLayer(LayerStack& layerStack)
    : Layer(layerStack)
{
    m_font.loadFromFile("data/NotoSans-Regular.ttf");

    m_title.setFont(m_font);
    m_title.setCharacterSize(128);
    m_title.setString("Starry Stealers");
    m_title.setPosition({32, 64});

    m_menu.addItem("Continue", []()
    {
        printf("Continue!\n");
    }, false);
    m_menu.addItem("New Game", [this]()
    {
        m_layerStack.pop();
        m_layerStack.push(Layer::Type::Game);
    });
    m_menu.addItem("Load Game", []()
    {
        printf("Load Game!\n");
    });
    m_menu.addItem("Settings", [this]()
    {
        m_layerStack.pop();
        m_layerStack.push(Layer::Type::Settings);
    });
    m_menu.addItem("Quit", [this]()
    {
        m_layerStack.clear();
    });
}

void MenuLayer::update(float dt)
{
    m_menu.update(dt);
}

void MenuLayer::draw()
{
    Renderer::Get().draw(m_title);

    m_menu.draw();
}

