#include "DebugDrawer.hpp"
#include "Renderer.hpp"
#include "Core/Math.hpp"

void DebugDrawer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    std::vector<sf::Vertex> verts(vertexCount);

    for (int i = 0; i < vertexCount; i++)
    {
        verts[i].position = {vertices[i].x, vertices[i].y};
        verts[i].color = {
			sf::Uint8(color.r * 255),
			sf::Uint8(color.g * 255),
			sf::Uint8(color.b * 255),
			sf::Uint8(color.a * 255)};
    }

    verts.push_back(verts[0]);

    Renderer.drawScaled(&verts[0], vertexCount, sf::LineStrip);
}

void DebugDrawer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    std::vector<sf::Vertex> verts(vertexCount);

    for (int i = 0; i < vertexCount; i++)
    {
        verts[i].position = {vertices[i].x, vertices[i].y};
		verts[i].color = {
			sf::Uint8(color.r * 255),
			sf::Uint8(color.g * 255),
			sf::Uint8(color.b * 255),
			sf::Uint8(color.a * 255)};
    }

    verts.push_back(verts[0]);

    // Renderer.draw(&verts[0], verts.size(), sf::TriangleFan);
    Renderer.drawScaled(&verts[0], verts.size(), sf::LineStrip);
}

void DebugDrawer::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
    printf("DrawCircle\n");
}

void DebugDrawer::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
    std::vector<sf::Vertex> verts(33);

    int i = 0;
    for (float angle = 0; angle <= M_PI*2 + M_PI/16; angle += M_PI/16)
    {
        verts[i].position = {
            (center.x) + (cos(angle) * radius),
            (center.y) + (sin(angle) * radius)
        };

        verts[i].color = {
			sf::Uint8(color.r * 255),
			sf::Uint8(color.g * 255),
			sf::Uint8(color.b * 255),
			sf::Uint8(color.a * 255)};
        i++;
    }

    Renderer.drawScaled(&verts[0], verts.size(), sf::LineStrip);
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
