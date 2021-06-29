// main.cpp : This file contains the 'main' function. Program execution begins and ends here.
#include <iostream>
#include <string>
#include <iomanip>
#include <thread>
#include <chrono>
#include <cmath>
#include "utils.h"
#include "tuple.h"
#include "point.h"
#include "vector.h"
#include "environment.h"
#include "projectile.h"
#include "canvas.h"
#include "Matrix2.h"
#include "Matrix3.h"
#include "Matrix4.h"

using namespace std::chrono_literals;

Projectile Tick(Environment env, Projectile proj) {
	Point new_position = proj.GetPosition() + proj.GetVelocity();
	Vector new_velocity = proj.GetVelocity() + env.GetGravity() + env.GetWind();
	return Projectile(new_position, new_velocity);
}

int main() {
	/*
	Point start(0, 1, 0);
	Vector velocity(1, 1.8, 0);
	Vector gravity(0, -0.1, 0);
	Vector wind(-0.01, 0, 0);
	Projectile proj = Projectile(start, velocity.normalize() * 10.15);
	Environment env = Environment(gravity, wind);

	Canvas c(900, 550);

	int count = 1;
	while (proj.GetPosition()[1] > 0) {
		proj = Tick(env, proj);
		std::cout << count << ": " << proj << std::endl;
		Point coordinate = proj.GetPosition();
		int x = round(coordinate[0]), y = round(coordinate[1]);
		c.WritePixel(x, (c.GetHeight() - y), Color(0, 1, 0));
		std::this_thread::sleep_for(100ms);
		count++;
	}
	
	std::string ppm = c.ToPPM();
	utils::ExportFile("test.ppm", ppm);
	*/

	Matrix4 A;

	Tuple t(2, 4, 6, 8);

	std::cout << A * t << std::endl;

	std::cin.get();
	return 0;
}
