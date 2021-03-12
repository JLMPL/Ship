#pragma once
#define _USE_MATH_DEFINES
#include <SFML/System/Vector2.hpp>
#include <cmath>

using vec2 = sf::Vector2f;
using vec2i = sf::Vector2i;

namespace math
{

float length(const vec2& v);
float distance(const vec2& a, const vec2& b);
vec2 normalize(const vec2& v);
float dot(const vec2& a, const vec2& b);
float cross(const vec2& a, const vec2& b);

}