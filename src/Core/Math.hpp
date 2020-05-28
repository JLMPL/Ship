#pragma once
#include <SFML/System/Vector2.hpp>

using vec2 = sf::Vector2f;

namespace math
{

float length(const sf::Vector2f& v);
sf::Vector2f normalize(const sf::Vector2f& v);
float dot(const sf::Vector2f& a, const sf::Vector2f& b);
float cross(const sf::Vector2f& a, const sf::Vector2f& b);

}