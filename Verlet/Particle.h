#pragma once
#include "vec2.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

struct Particle
{
	Vec2 pos, old_pos, acceleration = Vec2(0, 0);
	float radius;
	bool is_pinned;
	sf::Color color;
	sf::CircleShape shape;

	Particle(float x, float y, float r, sf::Color c, Vec2 starting_velocity = Vec2(0, 0), bool pinned = false) : 
		pos(Vec2(x, y)), radius(r), color(c), is_pinned(pinned) { 
		old_pos = pos - starting_velocity;

		shape = sf::CircleShape(radius);
		shape.setFillColor(color);
	}

	Particle(Vec2 p, float r, sf::Color c, Vec2 starting_velocity = Vec2(0, 0), bool pinned = false) : 
		pos(p), radius(r), color(c), is_pinned(pinned) { 
		old_pos = pos - starting_velocity;

		shape = sf::CircleShape(radius);
		shape.setFillColor(color);
	}

	
	void draw(sf::RenderWindow& window) {
		shape.setPosition(pos.x - radius, pos.y - radius);
		window.draw(shape);
	}

	void update_pos(float dt) {
		if (is_pinned) {
			pos = old_pos.copy();
			return;
		}

		Vec2 velocity = pos - old_pos;
		old_pos = pos.copy();

		pos += velocity;
		acceleration *= dt * dt; pos += acceleration; // Need two lines because += acceleration * dt * dt casued an error
		acceleration = Vec2(0, 0);
	}

	void accelerate(Vec2 accel) {
		acceleration += accel;
	}
};

