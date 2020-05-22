#include "Game.hpp"
#include "Renderer.hpp"

Game::Game()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    m_window.create(sf::VideoMode(1920, 1080), "Starry Stealers", sf::Style::Fullscreen, settings);
    Renderer::Get().init(m_window);

    m_layerStack.push(Layer::Type::Background);
    m_layerStack.push(Layer::Type::MainMenu);
}

void Game::processEvents()
{
    while (m_window.pollEvent(m_event))
    {
        if (m_event.type == sf::Event::Closed)
            m_window.close();
    }
}

void Game::update()
{
    if (m_clock.getElapsedTime().asSeconds() >= 1.f/60.f)
    {
        m_layerStack.update(1.f/60.f);

        if (m_layerStack.isEmpty())
            m_window.close();

        m_clock.restart();
    }
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