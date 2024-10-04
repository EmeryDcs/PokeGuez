#include <SFML/Graphics.hpp>
#include <cmath>

sf::Vector2f bezierQuadratic(const sf::Vector2f& p0, const sf::Vector2f& p1, const sf::Vector2f& p2, float t) {
    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;

    sf::Vector2f p = uu * p0 + 2 * u * t * p1 + tt * p2;
    return p;
}