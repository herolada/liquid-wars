#include "nation.h"
#include <iostream>
#include <cmath>
#include <unistd.h>
#include "Vector2fUtils.h"

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

Nation::Nation(std::vector<sf::Vector2f> units) : units(units) {
    rng = std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count());
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

void Nation::step(sf::Vector2f target) {
        // change position of each unit randomly
        for (auto& unit : units) {
            int target_x = 0;
            int target_y = 0;

            if (unit.x < target.x) {
                target_x = 1;
            } else if (unit.x > target.x) {
                target_x = -1;
            }

            if (unit.y < target.y) {
                target_y = 1;
            } else if (unit.y > target.y) {
                target_y = -1;
            }

            int randint_x = (int)(rand(rng) * (STEP_SIZE+1));
            int randint_y = (int)(rand(rng) * (STEP_SIZE+1));

            unit.x = unit.x  + target_x + randint_x;
            unit.y = unit.y  + target_y + randint_y;
        }
};

void Nation::create_unit() {
    sf::Vector2f unit_pos = {base.x, base.y};
    this->units.push_back(unit_pos);
};

sf::Vector2f Nation::get_base() {
    return this->base;
};

sf::Vector2f Nation::get_centre() {
    sf::Vector2f centre = {0,0};

    if (units.size() > 0) {
        for (auto unit : units) {
            centre += unit;
        }
        centre /= static_cast<float>(units.size());
    } else {
        centre = get_base();
    }
    return centre;
};

/* std::vector<sf::Vector2f> Nation::get_units() {
    return this->units;
}; */

void Nation::sort_units() {
    int i = 1;
    //std::vector<sf::Vector2f> sorted_v(v.size());
    //sorted_v[0] = v[0];

    while (i < units.size()) {
        int j = i-1;
        sf::Vector2f current = units[i];
        while (current < units[j]) {
            units[j+1] = units[j];
            j -= 1;
            if (j < 0) {
                break;
            }
        }
        units[j+1] = current; 
        i += 1;
    }

}