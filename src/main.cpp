#include <SFML/Graphics.hpp>
#include <random>
#include "nation.h"
#include "game.h"
#include <iostream>
#include <chrono>

#define NUM_UNITS 2000

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({600u, 600u}), "Liqud Wars", sf::Style::Default, sf::State::Windowed);
    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(60);
    window.setPosition({2800, 200});

    sf::Vector2f base_a = {100,100};
    Nation nation_a = Nation(base_a, NUM_UNITS);

    sf::Vector2f base_b = {500,500};
    Nation nation_b = Nation(base_b, NUM_UNITS);

    Game game(&nation_a, &nation_b);

    // base A
    sf::CircleShape base_a_m(20);
    sf::Color color_a(100, 250, 50);
    sf::Vector2f marker_offset(-20,-20);
    base_a_m.setFillColor(color_a);
    base_a_m.setPosition(nation_a.get_base()+marker_offset);

    // base B
    sf::CircleShape base_b_m(20);
    sf::Color color_b(250, 50, 100);
    base_b_m.setFillColor(color_b);
    base_b_m.setPosition(nation_b.get_base()+marker_offset);

    std::vector<sf::Vertex> units_m;

    for (int i=0; i< nation_a.get_units().size() + nation_b.get_units().size(); i++) {
        sf::Vertex unit_m;
        units_m.push_back(unit_m);
    }

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        game.step();

        window.clear();

        window.draw(base_a_m);
        window.draw(base_b_m);

        auto start = std::chrono::high_resolution_clock::now();

        std::vector<sf::Vector2f> units_a = nation_a.get_units();
        std::vector<sf::Vector2f> units_b = nation_b.get_units();

        for (int i=0; i<units_a.size(); i++) {
            units_m[i].color = color_a;
            units_m[i].position = units_a[i];
        }

        for (int i=0; i<units_b.size(); i++) {
            units_m[units_a.size() + i].color = color_b;
            units_m[units_a.size() + i].position = units_b[i];
        }

        window.draw(units_m.data(), units_m.size(), sf::PrimitiveType::Points);

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << duration.count() << std::endl;

        window.display();
    }
}
