#include <catch2/catch_test_macros.hpp>
#include "nation.h"
#include "game.h"
#include <iostream>
#include "Vector2fUtils.h"
#include <typeinfo>

TEST_CASE("Nation base is inside display")
{
    Nation nation = Nation();
    sf::Vector2f base = nation.get_base();
    REQUIRE(base.x >= 0);
    REQUIRE(base.y >= 0);
    REQUIRE(base.x < 600);
    REQUIRE(base.y < 600);
}

TEST_CASE("Sort sorts vector") {
    std::vector<sf::Vector2f> units = {{10,1},{1,10},{10,2},{2,10},{1,10}};
    Nation nation(units);

    nation.sort_units();

    REQUIRE(units.size() == nation.units.size());
    for (size_t i=0; i<nation.units.size()-1; i++) {

        REQUIRE(nation.units[i] <= nation.units[i+1]);
        REQUIRE((nation.units[i].x <= nation.units[i+1].x));
        if (nation.units[i].x == nation.units[i+1].x) {
            REQUIRE(nation.units[i].y <= nation.units[i+1].y);
        }
    }
}

TEST_CASE("Overtake works") {
    std::vector<sf::Vector2f> units_a = {{1,10},{10,100}};

    // THIS IS JUST TO DEFINE GAME, THE NATIONS ARE NOT BEING USED
    Nation nation_a = Nation();
    Nation nation_b = Nation();
    Game game(&nation_a, &nation_b);

    SECTION("no overtake") {
        std::vector<sf::Vector2f> units_b = {{2,10},{5,5},{9999,9999}};
        game.overtake(units_a, units_b);
        REQUIRE(units_a.size() == 2);
        REQUIRE(units_b.size() == 3);
    }
    SECTION("yes overtake") {
        std::vector<sf::Vector2f> units_b = {{10,100}};
        game.overtake(units_a, units_b);
        REQUIRE(units_a.size() == 3);
        REQUIRE(units_b.size() == 0);
    }
    SECTION("multiple same overtake") {
        std::vector<sf::Vector2f> units_b = {{1,10},{1,10}};
        game.overtake(units_a, units_b);
        REQUIRE(units_a.size() == 4);
        REQUIRE(units_b.size() == 0);
    }    
    SECTION("multiple diff overtake") {
        std::vector<sf::Vector2f> units_b = {{1,10},{10,100}};
        game.overtake(units_a, units_b);
        REQUIRE(units_a.size() == 4);
        REQUIRE(units_b.size() == 0);
    }
}


TEST_CASE("One unit overtakes another")
{
    Nation nation_a = Nation();
    Nation nation_b = Nation();
    std::vector<sf::Vector2f> units_a = {{90,90}};
    std::vector<sf::Vector2f> units_b = {{100,100}};
    sf::Vector2f target(100,100);
    nation_a.units = units_a;
    nation_b.units = units_b;

    Game game(&nation_a, &nation_b);

    const int max_steps = 1000;
    int steps = 0;
    while (steps < max_steps) {
        game.nation_step(&nation_a, &nation_b, target);

        if (nation_a.units.size() == 1 && nation_b.units.size() == 1) {
            CHECK(nation_a.units[0] != nation_b.units[0]);
        } else {
            REQUIRE(nation_a.units[0] == nation_b.units[0]);
            break;
        }
        steps++;
    }
    REQUIRE(steps < max_steps);
}