#include "Game.hpp"
#include "Renderer.hpp"
#include "Core/Timer.hpp"

static constexpr float FrameDuration = 1.f/60.f;

Game::Game()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    m_window.create(sf::VideoMode(1280, 720), "Starry Stealers", sf::Style::Close, settings);
    Renderer::get().init(m_window);

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
    // if (m_clock.getElapsedTime().asSeconds() >= FrameDuration)

    timer::delta = m_clock.restart().asSeconds();

    {
        m_layerStack.update(timer::delta);

        if (m_layerStack.isEmpty())
            m_window.close();

        // m_clock.restart();
    }
}

void Game::draw()
{
    Renderer::get().clear();
    m_layerStack.draw();
    Renderer::get().display();
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