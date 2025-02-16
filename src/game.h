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
    void step();
};

#endif