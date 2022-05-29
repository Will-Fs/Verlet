#pragma once
#include "Particle.h"
#include <iostream>
#include "Constants.h"
using namespace std;

struct Solver
{
	Vec2 gravity;

	Solver(Vec2 g) : gravity(g) {}

	void update(float dt, vector<Particle>& particles) {
		for (int i = (int)(1 / dt); i >= 0; i--) {
			apply_gravity(particles);
			solve_collisions(particles);
			apply_constraints(particles);
			update_positions(dt, particles);
		}
	}

	void apply_constraints(vector<Particle>& particles, float radius) {
		Vec2 center = Vec2(width/2, height/2);
		for (Particle& particle : particles) {

			Vec2 center_to_particle = particle.pos - center;
			float dist = center_to_particle.length();

			if (dist > radius - particle.radius) {
				Vec2 n = center_to_particle / dist;
				Vec2 move = n * (radius - particle.radius);
				particle.pos = center + move;
			}
		}
	}

	void apply_constraints(vector<Particle>& particles) {
		for (Particle& p : particles) {
			if (p.pos.x > width - p.radius)
				p.pos.x = width - p.radius;
			else if (p.pos.x < p.radius)
				p.pos.x = p.radius;

			if (p.pos.y > height - p.radius)
				p.pos.y = height - p.radius;
			else if (p.pos.y < p.radius)
				p.pos.y = p.radius;
		}
	}


	void solve_collisions(vector<Particle>& particles) {
		for (Particle& p1 : particles) {
			for (Particle& p2 : particles) {
				Vec2 collision_axis = p1.pos - p2.pos;
				float dist = collision_axis.length();
				float min_dist = p1.radius + p2.radius;

				if (dist < min_dist && dist != 0) {
					Vec2 n = collision_axis / dist;
					float delta = min_dist - dist;
					Vec2 move = n * delta * 0.5;

					p1.pos += move;
					p2.pos -= move;
				}

			}
		}
	}

	

	void apply_gravity(vector<Particle>& particles) {
		for (Particle& particle : particles)
			particle.accelerate(gravity);
	}

	void update_positions(float dt, vector<Particle>& particles) {
		for (Particle& particle : particles)
			particle.update_pos(dt);
	}



};

