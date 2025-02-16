#include "nation.h"
#include <iostream>

Nation::Nation() : base{0,0}
{
    
};

Nation::Nation(sf::Vector2f base, int num_units) : base(base), randint(-2,2)
{
    std::random_device dev;
    std::mt19937 rng(dev());

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

            unit.x = unit.x  + enemy_base_dir_x + randint(rng);
            unit.y = unit.y  + enemy_base_dir_y + randint(rng);
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