#pragma once
#include "Layers/LayerStack.hpp"
#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();
    ~Game() = default;

    void run();

private:
    void processEvents();
    void update();
    void draw();

private:
    sf::RenderWindow m_window;
    sf::Event m_event;
    sf::Clock m_clock;

    LayerStack m_layerStack;
};