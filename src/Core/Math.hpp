#pragma once
#include <SFML/System/Vector2.hpp>

namespace math
{

float length(const sf::Vector2f& v);
sf::Vector2f normalize(const sf::Vector2f& v);
float cross(const sf::Vector2f& a, const sf::Vector2f& b);

}