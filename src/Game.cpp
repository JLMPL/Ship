#include "Game.hpp"
#include "Renderer.hpp"
#include "Core/Timer.hpp"
#include "Scene/Overworld.hpp"
#include "Random.hpp"
#include "Core/Config.hpp"

static constexpr float FrameDuration = 1.f/60.f;

Game::Game()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    m_window.create(sf::VideoMode(DisplayWidth, DisplayHeight), "Starry Stealers", sf::Style::Fullscreen, settings);

    Renderer::get().init(m_window);
    rng::randomizeSeed();

    changeScene(new Overworld(this));
}

void Game::changeScene(Scene* scene)
{
    m_nextScene = scene;
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
    timer::delta = m_clock.restart().asSeconds();

    if (m_nextScene)
    {
        m_scene.reset(m_nextScene);
        m_nextScene = nullptr;
    }

    if (m_scene)
        m_scene->update(timer::delta);

    if (!m_scene)
        m_window.close();
}

void Game::draw()
{
    Renderer::get().clear();
    m_scene->draw();
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