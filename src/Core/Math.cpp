#include "Math.hpp"
#include <cmath>

namespace math
{

float length(const sf::Vector2f& v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

sf::Vector2f normalize(const sf::Vector2f& v)
{
    float len = length(v);

    return sf::Vector2f(
        v.x / len,
        v.y / len
    );
}

float cross(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return (a.x*b.y) - (a.y*b.x);
}

}