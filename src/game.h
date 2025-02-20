#ifndef GAME_H
#define GAME_H

#include "nation.h"

class Game
{
private:
    Game();

    Nation* nation_a;
    Nation* nation_b;

    std::mt19937 rng;
    std::uniform_real_distribution<float> rand;
public:
    Game(Nation* nation_a, Nation* nation_b);
    int check_win();
    void step(sf::Vector2f target_a, sf::Vector2f target_b);
    void nation_step(Nation* nation_a, Nation* nation_b, sf::Vector2f target);
    void overtake(std::vector<sf::Vector2f>& units_a, std::vector<sf::Vector2f>& units_b);
};

#endif