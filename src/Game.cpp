#include "Game.hpp"
#include "Renderer.hpp"
#include "Random.hpp"
#include "Core/Timer.hpp"
#include "Core/Config.hpp"
#include "Input/Input.hpp"
#include "Scene/Overworld.hpp"
#include "Scene/MainMenu.hpp"
#include "Audio/Audio.hpp"

static constexpr float FrameDuration = 1.f/60.f;

Game::Game()
{
    DisplayWidth = sf::VideoMode::getDesktopMode().width;
    DisplayHeight = sf::VideoMode::getDesktopMode().height;

    DisplayWidth = 1280;
    DisplayHeight = 720;

    // m_window.create(sf::VideoMode::getDesktopMode(), "Starry Stealers", sf::Style::Fullscreen);
    m_window.create(sf::VideoMode(DisplayWidth, DisplayHeight), "Starry Stealers", sf::Style::Close);
    m_window.setMouseCursorGrabbed(true);
    m_window.setMouseCursorVisible(false);

    Renderer.init(m_window);
    rng::randomizeSeed();
    Input.init();

    changeScene(new MainMenu(this));
	// changeScene(new Overworld(this));

}

void Game::changeScene(Scene* scene)
{
    m_nextScene = scene;

    if (!m_nextScene)
        m_window.close();
}

void Game::processEvents()
{
    while (m_window.pollEvent(m_event))
    {
        if (m_event.type == sf::Event::Closed)
            m_window.close();
        if (m_event.type == sf::Event::KeyPressed &&
            m_event.key.code == sf::Keyboard::F8)
        {
            m_scene->setPause(true);
        }
        if (m_event.type == sf::Event::KeyPressed &&
            m_event.key.code == sf::Keyboard::F9)
        {
            m_scene->setPause(false);
        }
    }
}

void Game::update()
{
    timer::delta = m_clock.restart().asSeconds();

    Input.update();

    if (m_nextScene)
    {
        m_scene.reset(m_nextScene);
        m_nextScene = nullptr;
    }

    if (m_scene)
        m_scene->update(timer::delta);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
        m_window.close();

    Audio.updateVolumes();
    Renderer.update();
}

void Game::draw()
{
    Renderer.clear();

    if (m_scene)
        m_scene->draw();

    Input.debugDraw();
    Renderer.display();
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