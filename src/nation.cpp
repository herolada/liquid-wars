#include "nation.h"
#include <iostream>
#include <cmath>
#include <unistd.h>

#define STEP_SIZE 2

Nation::Nation() : rand(-1,1)
{
    //std::random_device dev;
    //std::mt19937 rng(dev());

    rng = std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count());

    for (int i = 0; i < 10; ++i) {
        sf::Vector2f unit_pos = {base.x, base.y};
        units.push_back(unit_pos);
    }

    int base_x = abs((int)(rand(rng) * 600));
    int base_y = abs((int)(rand(rng) * 600));
    base = sf::Vector2f(base_x, base_y);

};

Nation::Nation(sf::Vector2f base, int num_units) : base(base), rand(-1,1)
{
    //std::random_device dev;
    //std::mt19937 rng(dev());

    rng = std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count());

    for (int i = 0; i < num_units; ++i) {
        sf::Vector2f unit_pos = {base.x, base.y};
        units.push_back(unit_pos);
    }
};

void Nation::step(sf::Vector2f enemy_base) {
        // change position of each unit randomly
        for (auto& unit : units) {
            int enemy_base_dir_x = 0;
            int enemy_base_dir_y = 0;

            if (unit.x < enemy_base.x) {
                enemy_base_dir_x = 1;
            } else if (unit.x > enemy_base.x) {
                enemy_base_dir_x = -1;
            }

            if (unit.y < enemy_base.y) {
                enemy_base_dir_y = 1;
            } else if (unit.y > enemy_base.y) {
                enemy_base_dir_y = -1;
            }

            int randint_x = (int)(rand(rng) * (STEP_SIZE+1));
            int randint_y = (int)(rand(rng) * (STEP_SIZE+1));

            unit.x = unit.x  + enemy_base_dir_x + randint_x;
            unit.y = unit.y  + enemy_base_dir_y + randint_y;
        }
};

void Nation::create_unit() {
    sf::Vector2f unit_pos = {base.x, base.y};
    this->units.push_back(unit_pos);
};

sf::Vector2f Nation::get_base() {
    return this->base;
};

std::vector<sf::Vector2f> Nation::get_units() {
    return this->units;
};