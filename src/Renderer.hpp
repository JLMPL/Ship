#pragma once
#include <SFML/Graphics.hpp>

class Renderer
{
private:
    Renderer() = default;
    ~Renderer() = default;

public:
    void init(sf::RenderWindow& window);

    void draw(sf::Text& text);
    void draw(sf::Vertex* verts, int num, sf::PrimitiveType type);

    static Renderer& Get()
    {
        static Renderer renderer;
        return renderer;
    }

private:
    sf::RenderWindow* m_window;
};
