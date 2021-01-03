#pragma once
#include "Core/Math.hpp"
#include <SFML/Graphics.hpp>

class Renderer
{
private:
    Renderer() = default;
    ~Renderer() = default;

public:
    void init(sf::RenderWindow& window);

    void update();

    void shake(float strength, float duration);

    void clear();
    void display();

    void draw(sf::Drawable& dw);
    void draw(sf::Vertex* verts, int num, sf::PrimitiveType type, const sf::RenderStates& rs = sf::RenderStates::Default);

    void drawScaled(sf::Drawable& dw);
    void drawScaled(sf::Vertex* verts, int num, sf::PrimitiveType type, const sf::RenderStates& rs = sf::RenderStates::Default);
    void drawLineScaled(const vec2& a, const vec2& b, const sf::Color& color);

    void setView(const vec2& pos);
    void setZoom(float zoom);
    vec2 getViewWorldPosition() const;

    vec2 getGlobalMousePosition();
    vec2 getLocalMousePosition() const;

    void setLocalMousePosition(const vec2& pos);

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
    vec2 m_viewPos;

    sf::Clock m_clock;
    sf::Clock m_shaker;

    float m_zoom = 0.05f;

    bool m_isShake = false;
    float m_shakeStrength = 1.f;
    float m_shakeDuration = 0.f;
};
