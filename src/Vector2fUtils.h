#ifndef VECTOR2F_UTILS_H
#define VECTOR2F_UTILS_H

#include <SFML/Graphics.hpp>

namespace sf {
    template <typename T>
    constexpr bool operator<(sf::Vector2<T> left, sf::Vector2<T> right)
    {
        return (left.x < right.x) || (left.x == right.x && left.y < right.y);
    };

    template <typename T>
    constexpr bool operator<=(sf::Vector2<T> left, sf::Vector2<T> right)
    {
        return (left.x < right.x) || (left.x == right.x && left.y <= right.y);
    };
}

#endif // VECTOR2F_UTILS_H
