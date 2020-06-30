#include "Math.hpp"
#include <cmath>

namespace math
{

float length(const vec2& v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

float distance(const vec2& a, const vec2& b)
{
    return length(a - b);
}

vec2 normalize(const vec2& v)
{
    float len = length(v);

    return vec2(
        v.x / len,
        v.y / len
    );
}

float dot(const vec2& a, const vec2& b)
{
    return (a.x * b.x + a.y * b.y);
}

float cross(const vec2& a, const vec2& b)
{
    return (a.x*b.y) - (a.y*b.x);
}

}