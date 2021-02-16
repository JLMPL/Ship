#pragma once
#include "Core/Math.hpp"
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <string>
#include <vector>

class Mesh
{
public:
    Mesh() = default;
    ~Mesh() = default;

    void loadFromFile(const std::string& path);

    void setPosition(const vec2& pos);
    void setOffset(const vec2& offset);
    void setRotation(float rot);
    void setScale(float scale);
    void setScale(const vec2& scale);

    void draw(bool scaled = true);

private:
    std::vector<sf::Vertex> m_verts;

    vec2 m_position;
    vec2 m_offset;
    float m_rotation = 0;
    vec2 m_scale = {1,1};
    sf::Transform m_tr;
};