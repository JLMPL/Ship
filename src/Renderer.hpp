#pragma once
#include <SFML/Graphics.hpp>

class Renderer
{
private:
    Renderer() = default;
    ~Renderer() = default;

public:
    void init(sf::RenderWindow& window);

    void clear();
    void display();

    void draw(sf::Drawable& dw);
    void draw(sf::Vertex* verts, int num, sf::PrimitiveType type, const sf::RenderStates& rs = sf::RenderStates::Default);

    void drawScaled(sf::Drawable& dw);
    void drawScaled(sf::Vertex* verts, int num, sf::PrimitiveType type, const sf::RenderStates& rs = sf::RenderStates::Default);
    void drawLineScaled(const sf::Vector2f& a, const sf::Vector2f& b, const sf::Color& color);

    void setView(const sf::Vector2f& pos);
    void setZoom(float zoom);
    sf::Vector2f getViewWorldPosition() const;

    sf::Vector2f getGlobalMousePosition();
    sf::Vector2f getLocalMousePosition() const;

    static Renderer& get()
    {
        static Renderer renderer;
        return renderer;
    }

private:
    sf::RenderWindow* m_window;
    sf::RenderTexture m_sceneTarget;
    sf::RenderTexture m_uiTarget;
    sf::View m_view;

    float m_zoom = 0.05f;
};
