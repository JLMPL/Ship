#include "DebugDrawer.hpp"
#include "Renderer.hpp"

void DebugDrawer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    std::vector<sf::Vertex> verts(vertexCount);

    for (int i = 0; i < vertexCount; i++)
    {
        verts[i].position = {vertices[i].x, vertices[i].y};
        verts[i].color = {color.r * 255, color.g * 255, color.b * 255, color.a * 255};
    }

    verts.push_back(verts[0]);

    Renderer::Get().draw(&verts[0], vertexCount, sf::LineStrip);
}

void DebugDrawer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    std::vector<sf::Vertex> verts(vertexCount);

    for (int i = 0; i < vertexCount; i++)
    {
        verts[i].position = {vertices[i].x * 32, vertices[i].y * 32};
        verts[i].color = {color.r * 255, color.g * 255, color.b * 255, color.a * 255};
    }

    verts.push_back(verts[0]);

    // Renderer::Get().draw(&verts[0], verts.size(), sf::TriangleFan);
    Renderer::Get().draw(&verts[0], verts.size(), sf::LineStrip);
}

void DebugDrawer::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{

}

void DebugDrawer::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{

}

void DebugDrawer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{

}

void DebugDrawer::DrawTransform(const b2Transform& xf)
{

}

void DebugDrawer::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{

}
