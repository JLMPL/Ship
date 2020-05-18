#include "Game.hpp"
#include "Renderer.hpp"

Game::Game()
{
    m_window.create(sf::VideoMode(1280,720), "Starry Stealers", sf::Style::Close);
    Renderer::Get().init(m_window);

    m_layerStack.push(Layer::Type::Background);
    m_layerStack.push(Layer::Type::MainMenu);
}

void Game::processEvents()
{
    while (m_window.pollEvent(m_event))
    {
        if (m_event.type == sf::Event::Closed ||
            (m_event.type == sf::Event::KeyPressed &&
             m_event.key.code == sf::Keyboard::Escape))
        {
            m_window.close();
        }
    }
}

void Game::update()
{
    float dt = m_clock.restart().asSeconds();

    m_layerStack.update(dt);

    if (m_layerStack.isEmpty())
        m_window.close();
}

void Game::draw()
{
    m_window.clear();
    m_layerStack.draw();
    m_window.display();
}

void Game::run()
{
    while (m_window.isOpen())
    {
        processEvents();
        update();
        draw();
    }
}