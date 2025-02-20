#include <stdio.h>
#include "nation.h"
#include "game.h"
#include <algorithm>
#include "Vector2fUtils.h"
#include <iostream>
#include <typeinfo>

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

    for (auto& unit : nation_a->units) {
        if (unit == base_b) {
            win_a = true;
            break;
        }
    }

    for (auto& unit : nation_b->units) {
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

void Game::nation_step(Nation* nation_a, Nation* nation_b, sf::Vector2f target) {
    nation_a->step(target);
    nation_a->sort_units();
    nation_b->sort_units();
    overtake(nation_a->units, nation_b->units);
}

void Game::step(sf::Vector2f target_a, sf::Vector2f target_b) {
    if (rand(rng) < 0.5) {
        nation_step(nation_a, nation_b, target_a);
        nation_step(nation_b, nation_a, target_b);
    } else {
        nation_step(nation_b, nation_a, target_b);
        nation_step(nation_a, nation_b, target_a);
    }
};


void Game::overtake(std::vector<sf::Vector2f>& units_a, std::vector<sf::Vector2f>& units_b) {
    std::vector<std::vector<sf::Vector2f>::iterator> ids_to_erase;

    for (auto unit = units_b.begin(); unit != units_b.end(); ++unit) {

        // repeated binary search
        std::vector<sf::Vector2f>::iterator id = units_a.begin();
        id = std::lower_bound(id, units_a.end(), *unit);

        if (id != units_a.end() && *id == *unit) {
            units_a.insert(id,*unit);
            ids_to_erase.push_back(unit);
        }
    }
    std::reverse(ids_to_erase.begin(), ids_to_erase.end());
    for (auto id : ids_to_erase) {
        units_b.erase(id);
    }
}