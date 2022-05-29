#include <SFML/Graphics.hpp>
#include <iostream>
#include "vec2.h"

using namespace std;

void draw(float width, float height, sf::RenderWindow &window) {

    sf::CircleShape shape(200.f, 100);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(300 - 200, 300 - 200);

    window.draw(shape);
}

void init(sf::RenderWindow &window, float width, float height) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    window.create(sf::VideoMode(width, height), "Verlet", sf::Style::Close, settings);
}

int main()
{
    float width = 600, height = 600;
    
    sf::RenderWindow window;
    init(window, width, height);

    while (window.isOpen())
    {
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        draw(width, height, window);

        window.display();
    }

    return 0;
}