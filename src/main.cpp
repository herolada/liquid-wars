#include <SFML/Graphics.hpp>
#include <random>
#include "nation.h"
#include <iostream>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({600u, 600u}), "Liqud Wars", sf::Style::Default, sf::State::Windowed);
    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(60);
    window.setPosition({2800, 200});

    //std::random_device dev;
    //std::mt19937 rng(dev());
    //std::uniform_int_distribution<std::mt19937::result_type> randint(0,600);

    sf::Vector2f base_a = {100,100};
    Nation nation_a = Nation(base_a, 10);

    sf::Vector2f base_b = {500,500};
    Nation nation_b = Nation(base_b, 10);

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

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        nation_a.step(nation_b.get_base());

        window.clear();

        window.draw(base_a_m);
        window.draw(base_b_m);

        for (sf::Vector2f unit : nation_a.get_units()) {
            sf::CircleShape unit_m(2);
            unit_m.setFillColor(color_a);
            unit_m.setPosition(unit);
            window.draw(unit_m);
        }

        window.display();
    }
}
