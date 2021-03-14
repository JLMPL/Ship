#pragma once
#include "Core/Math.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <vector>

class Trail
{
public:
    Trail() = default;

    void update();
    void draw();

    void setPosition(const vec2& pos);
    void setColor(const sf::Color& color);
    void setInterval(float interval);
    void setLength(int length);

private:
    std::vector<sf::Vertex> m_verts;
    sf::Time m_timer = sf::seconds(1);
    sf::Color m_color = {255,255,255,255};
    float m_interval = 0.1;
    vec2 m_pos;
    int m_length = 100;
};