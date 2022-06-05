#pragma once
#include "Particle.h"
#include "vec2.h"

struct Spring {
	Particle p1, p2;
	float length, k;

	Spring(Particle p1, Particle p2, float k, float length) : p1(p1), p2(p2), k(k), length(length) {}
	Spring(Particle p1, Particle p2, float k) : p1(p1), p2(p2), k(k) { length = p1.pos.dist(p2.pos); }

	void update() {
		Vec2 p1_to_p2 = p1.pos - p2.pos;
		float dist = p1_to_p2.length();
		float dx = dist - length;

		p1_to_p2.normalize();
		Vec2 move = p1_to_p2 * -k * dx;

		p1.accelerate(move);
		move *= -1; p2.accelerate(move);
	}
};