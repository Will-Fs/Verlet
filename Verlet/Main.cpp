#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "vec2.h"
#include "Particle.h"
#include "Solver.h"
#include "Constants.h"

using namespace std;

void draw_all(vector<Particle> particles, sf::RenderWindow& window) {
    for (Particle particle : particles)
        particle.draw(window);
}

void init(sf::RenderWindow &window) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    window.create(sf::VideoMode((int)width, (int)height), "Verlet", sf::Style::Close, settings);
    window.setFramerateLimit(60);
}

int main()
{
    float dt = 0.2f;

    vector<Particle> particles;

    Solver solver = Solver({0, 1});

    sf::CircleShape constraintShape = sf::CircleShape(constraint_radius_const, 50);
    constraintShape.setFillColor(sf::Color::Transparent);
    constraintShape.setOutlineColor(sf::Color::White);
    constraintShape.setOutlineThickness(-1);
    constraintShape.setPosition(width/2 - constraint_radius_const, height/2 - constraint_radius_const);
    
    sf::RenderWindow window;
    sf::Text framerate_text;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        cout << "ERROR LOADING FONT!";
    else
        framerate_text.setFont(font);

    framerate_text.setCharacterSize(20);
    framerate_text.setPosition(5, 5);
    framerate_text.setFillColor(sf::Color::White);

    init(window);
    float theta = 0;
    float d_theta = 0.01f;
    int frame_num = 0;

    sf::Clock clock;
    float last_time = 0;

    while (window.isOpen())
    {
        window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        if (frame_num % 1 == 0 && particles.size() < 500) 
            particles.push_back(Particle(Vec2(width / 2, 10), 5, sf::Color{(uint8_t)(255 *  + sin(theta)), 100, 100}, Vec2(cos(theta), sin(theta))));

        solver.update(dt, particles);
        draw_all(particles, window);
        //window.draw(constraintShape);

        theta += d_theta;
        if (theta > M_PI || theta < 0)
            d_theta *= -1;
        frame_num++;

        float current_time = clock.restart().asSeconds();
        float fps = 1.f / current_time;
        last_time = current_time;

        framerate_text.setString("FPS: " + to_string((int)floor(fps + 0.5)) + "\nNumber of particles: " + to_string(particles.size()));
        window.draw(framerate_text);

        window.display();
    }

    return 0;
}