#include <catch2/catch_test_macros.hpp>
#include "nation.h"

TEST_CASE("Nation base is inside display")
{
    Nation nation = Nation();
    sf::Vector2f base = nation.get_base();
    REQUIRE(base.x >= 0);
    REQUIRE(base.y >= 0);
    REQUIRE(base.x < 600);
    REQUIRE(base.y < 600);
}