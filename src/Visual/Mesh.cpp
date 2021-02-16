#include "Mesh.hpp"
#include "Renderer.hpp"
#include <fstream>
#include <cmath>

std::map<std::string, sf::Color> lookup = {
    {"White",     sf::Color(0xffffffff)},
    {"LightGray", sf::Color(0xC0C0C0ff)},
    {"Gray",      sf::Color(0x808080ff)},
    {"DarkGray",  sf::Color(0x404040ff)},
    {"Blue",      sf::Color(0x0000ffff)},
    {"DarkBlue",  sf::Color(0x000080ff)},
    {"Red",       sf::Color(0xff0000ff)},
    {"DarkRed",   sf::Color(0x800000ff)},
    {"Error",     sf::Color(0xff00ffff)}
};

struct Triangle
{
    sf::Color color;
    int index[3] = {0};
};

void Mesh::loadFromFile(const std::string& path)
{
    std::vector<vec2> positions;
    std::vector<Triangle> tris;

    std::ifstream file(path.c_str());

    if (!file.good())
        printf("Error: could not load %s\n", path.c_str());

    sf::Color currentColor = lookup["Error"];

    while (!file.eof())
    {
        std::string line;
        std::getline(file, line);

        if (line[0] == 'v')
        {
            vec2 pos;
            float junk;
            sscanf(line.c_str(), "v %f %f %f", &pos.x, &junk, &pos.y);
            positions.push_back(pos);
        }

        if (line.substr(0, 6) == "usemtl")
        {
            std::string color = line.substr(7, line.size()-7);

            if (lookup.find(color) != lookup.end())
                currentColor = lookup[color];
            else
                currentColor = lookup["Error"];
        }

        if (line[0] == 'f')
        {
            Triangle tri;
            tri.color = currentColor;
            sscanf(line.c_str(), "f %d %d %d", &tri.index[0], &tri.index[1], &tri.index[2]);
            tri.index[0]--; tri.index[1]--; tri.index[2]--;
            tris.push_back(tri);
        }
    }

    for (auto& tri : tris)
    {
        m_verts.push_back(sf::Vertex(positions[tri.index[0]], tri.color));
        m_verts.push_back(sf::Vertex(positions[tri.index[1]], tri.color));
        m_verts.push_back(sf::Vertex(positions[tri.index[2]], tri.color));
    }

    // for (auto& vert : m_verts)
    //     printf("sf::v %f %f\n", vert.position.x, vert.position.y);
}

void Mesh::setPosition(const vec2& pos)
{
    m_position = pos;
}

void Mesh::setOffset(const vec2& offset)
{
    m_offset = offset;
}

void Mesh::setRotation(float rot)
{
    m_rotation = rot;
}

void Mesh::setScale(float scale)
{
    m_scale = {scale, scale};
}

void Mesh::setScale(const vec2& scale)
{
    m_scale = scale;
}

void Mesh::draw(bool scaled)
{
    m_tr = sf::Transform();
    m_tr.translate(m_position).
        rotate(m_rotation * (180.f/M_PI)).
        translate(m_offset).
        scale(m_scale);

    if (scaled)
        Renderer::get().drawScaled(m_verts.data(), m_verts.size(), sf::Triangles, sf::RenderStates(m_tr));
    else
        Renderer::get().draw(m_verts.data(), m_verts.size(), sf::Triangles, sf::RenderStates(m_tr));

}
