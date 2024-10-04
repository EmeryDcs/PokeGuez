#include <SFML/Graphics.hpp>
#include <cmath>
#ifndef BEZIER_H
#define BEZIER_H

sf::Vector2f bezierQuadratic(const sf::Vector2f& p0, const sf::Vector2f& p1, const sf::Vector2f& p2, float t);

#endif // EXO1_H