#pragma once
#include "Particle.h"
#include "vec2.h"

struct Link {
	Particle p1, p2;
	float length;

	Link(Particle p1, Particle p2, float length) : p1(p1), p2(p2), length(length) {}
	Link(Particle p1, Particle p2) : p1(p1), p2(p2) { length = p1.pos.dist(p2.pos); }

	void update() {
		Vec2 p1_to_p2 = p1.pos - p2.pos;
		float dist = p1_to_p2.length();

		if (dist == length) return;

		float delta = length - dist;
		p1_to_p2.normalize();

		Vec2 move = p1_to_p2 * delta * 0.5;
		p1.pos += move;
		p2.pos -= move;
	}
};