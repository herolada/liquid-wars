#include <stdio.h>
#include "nation.h"
#include "game.h"

/* Game::Game() : nation_a(&Nation()), nation_b(&Nation()), rand(0,1) {
    std::random_device dev;
    std::mt19937 rng(dev());
}; */

Game::Game(Nation* nation_a, Nation* nation_b) 
    : nation_a(nation_a), nation_b(nation_b), rand(0,1) {
    std::random_device dev;
    std::mt19937 rng(dev());
};

int Game::check_win() {
    sf::Vector2f base_a = nation_a->get_base();
    sf::Vector2f base_b = nation_b->get_base();

    bool win_a = false;
    bool win_b = false;

    for (auto& unit : nation_a->get_units()) {
        if (unit == base_b) {
            win_a = true;
            break;
        }
    }

    for (auto& unit : nation_b->get_units()) {
        if (unit == base_a) {
            win_b = true;
            break;
        }
    }

    if (win_a && win_b) {
        if (rand(rng) < 0.5) {
            return 0;
        } else {
            return 1;
        }
    }
    if (win_a) {return 0;}
    if (win_b) {return 1;}
    return -1;
};

void Game::step() {
    if (rand(rng) < 0.5) {
        
        nation_a->step(nation_b->get_base());
        nation_b->step(nation_a->get_base());
    } else {
        nation_b->step(nation_a->get_base());
        nation_a->step(nation_b->get_base());
    }
};

