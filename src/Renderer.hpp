#pragma once
#include <SFML/Graphics.hpp>

class Renderer
{
private:
    Renderer() = default;
    ~Renderer() = default;

public:
    void init(sf::RenderWindow& window);

    void draw(sf::Drawable& dw);
    void draw(sf::Vertex* verts, int num, sf::PrimitiveType type, const sf::RenderStates& rs = sf::RenderStates::Default);

    void drawScaled(sf::Vertex* verts, int num, sf::PrimitiveType type, const sf::RenderStates& rs = sf::RenderStates::Default);
    void drawLineScaled(const sf::Vector2f& a, const sf::Vector2f& b, const sf::Color& color);

    void setView(const sf::Vector2f& pos);

    sf::Vector2f getGlobalMousePosition() const;
    sf::Vector2f getLocalMousePosition() const;

    static Renderer& get()
    {
        static Renderer renderer;
        return renderer;
    }

private:
    sf::RenderWindow* m_window;
    sf::View m_view;
};
