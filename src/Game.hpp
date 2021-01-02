#pragma once
#include "Scene/Scene.hpp"
#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();
    ~Game() = default;

    void run();

    void changeScene(Scene* scene);

private:
    void processEvents();
    void update();
    void draw();

private:
    sf::RenderWindow m_window;
    sf::Event m_event;
    sf::Clock m_clock;

    Scene* m_nextScene = nullptr;
    Scene::Ptr m_scene = nullptr;
};