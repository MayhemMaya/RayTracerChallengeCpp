// main.cpp : This file contains the 'main' function. Program execution begins and ends here.
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <array>
#include "utils.h"
#include "tuple.h"
#include "point.h"
#include "vector.h"
#include "environment.h"
#include "projectile.h"
#include "canvas.h"
#include "matrix2.h"
#include "matrix3.h"
#include "matrix4.h"
#include "translation-matrix.h"
#include "scaling-matrix.h"
#include "rotation-matrix.h"
#include "shearing-matrix.h"
#include "ray.h"
#include "intersection.h"
#include "hit.h"
#include "object.h"
#include "sphere.h"

int main() {
	Point ray_origin(0, 0, -5);

	float wall_z = 10;
	float wall_size = 7.0;
	int canvas_pixels = 100;

	float pixel_size = wall_size / canvas_pixels;
	float half = wall_size / 2;

	Canvas c(canvas_pixels, canvas_pixels);
	Color red(1, 0, 0);
	Sphere sphere;
	//sphere.SetTransform(RotationMatrix(0, 0, utils::kPI / 4) * ScalingMatrix(0.5, 1, 1));
	sphere.SetTransform(ShearingMatrix(1, 0, 0, 0, 0, 0) * ScalingMatrix(0.5, 1, 1));
	//sphere.SetTransform(TranslationMatrix(0.5, 0, 0) * RotationMatrix(0, 0, utils::kPI / 4) * ScalingMatrix(0.5, 1, 1));
	std::cout << sphere.GetTransform() << std::endl;

	for (int y = 0; y < canvas_pixels; y++) {
		float world_y = half - pixel_size * y;
		for (int x = 0; x < canvas_pixels; x++) {
			float world_x = -half + pixel_size * x;

			Point position(world_x, world_y, wall_z);
			Ray r(ray_origin, (position - ray_origin).normalize());
			std::vector<Intersection> xs = r.intersect(sphere);
			if (Hit::hit(xs).result == HitResult::HIT) {
				c.WritePixel(x, y, red);
			}
		}
	}
	utils::ExportFile("sphere.ppm", c.ToPPM());

	std::cin.get();
	return 0;
}
