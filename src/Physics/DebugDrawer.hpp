#pragma once
#include "Libs/box2d/box2d.h"

class DebugDrawer : public b2Draw
{
public:
    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override final;
    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override final;
    void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override final;
    void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override final;
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override final;
    void DrawTransform(const b2Transform& xf) override final;
    void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override final;
};