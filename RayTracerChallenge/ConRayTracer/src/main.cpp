// main.cpp : This file contains the 'main' function. Program execution begins and ends here.
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include "utils.h"
#include "tuple.h"
#include "point.h"
#include "vector.h"
#include "environment.h"
#include "projectile.h"

using namespace std::chrono_literals;

Projectile Tick(Environment env, Projectile proj) {
	Point new_position = proj.GetPosition() + proj.GetVelocity();
	Vector new_velocity = proj.GetVelocity() + env.GetGravity() + env.GetWind();
	return Projectile(new_position, new_velocity);
}

int main() {
	
	Environment env = Environment(Vector(0, -0.1, 0), Vector(-0.01, 0, 0));
	Projectile proj = Projectile(Point(0, 1, 0), Vector(1, 1, 0).normalize());
	int count = 1;
	while (proj.GetPosition()[1] > 0) {
		proj = Tick(env, proj);
		std::cout << count << ": " << proj << std::endl;
		std::this_thread::sleep_for(250ms);
		count++;
	}

	std::cin.get();
	return 0;
}
