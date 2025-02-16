#ifndef NATION_H
#define NATION_H

#include <vector>
#include <tuple>
#include <SFML/Graphics.hpp>
#include <random>

/* struct Position {
    int x;
    int y;
}; */

class Nation
{
private:
    sf::Vector2f base;
    std::vector<sf::Vector2f> units;

    std::mt19937 rng;
    std::uniform_int_distribution<int> randint;

public:
    Nation();
    Nation(sf::Vector2f base, int num_units);
    void step(sf::Vector2f enemy_base);
    void create_unit();
    sf::Vector2f get_base();
    std::vector<sf::Vector2f> get_units();
};

#endif