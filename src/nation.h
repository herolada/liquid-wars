#ifndef NATION_H
#define NATION_H

#include <vector>
#include <tuple>
#include <SFML/Graphics.hpp>
#include <random>

class Nation
{
private:
    sf::Vector2f base;
    std::mt19937 rng;
    std::uniform_real_distribution<float> rand;

public:
    std::vector<sf::Vector2f> units;

    Nation();
    Nation(std::vector<sf::Vector2f> units);
    Nation(sf::Vector2f base, int num_units);
    void step(sf::Vector2f enemy_base);
    void create_unit();
    sf::Vector2f get_base();
    //std::vector<sf::Vector2f> get_units();
    sf::Vector2f get_centre();
    void sort_units();
};

#endif