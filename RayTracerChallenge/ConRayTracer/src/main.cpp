// main.cpp : This file contains the 'main' function. Program execution begins and ends here.
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "ray-tracer.h"

int main() {

	int res_x = 200;
	int res_y = 100;

	World world = World(WorldType::EMPTY);

	Plane floor("floor", Matrix4().scaling(10.0f, 0.01f, 10.0f));
	Material floor_mat;
	CheckerPattern floor_pattern = CheckerPattern(Colors::DarkGrey, Colors::White);
	floor_pattern.SetTransform(Matrix4().scaling(0.125, 0.125, 0.125));
	floor_mat.SetPattern(&floor_pattern);
	floor_mat.SetSpecular(0.0f);
	floor.SetMaterial(floor_mat);

	Sphere middle("middle", Matrix4().translation(-0.5f, 1.0f, 0.5f));
	StripePattern middle_pattern = StripePattern(Colors::White, Colors::Purple);
	middle_pattern.SetTransform(Matrix4().scaling(0.25, 0.25, 0.25));
	Material middle_mat;
	middle_mat.SetPattern(&middle_pattern);
	middle_mat.SetDiffuse(0.7f);
	middle_mat.SetSpecular(0.3f);
	middle.SetMaterial(middle_mat);

	Sphere right("right", Matrix4().translation(1.5f, 0.5f, -0.5f) * Matrix4().scaling(0.5f, 0.5f, 0.5f));
	Material right_mat;
	right_mat.SetColor(Color(0.5f, 1.0f, 0.1f));
	right_mat.SetDiffuse(0.7f);
	right_mat.SetSpecular(0.3f);
	right.SetMaterial(right_mat);

	Sphere left("left", Matrix4().translation(-1.5f, 0.33f, -0.75f) * Matrix4().scaling(0.33f, 0.33f, 0.33f));
	Material left_mat;
	left_mat.SetColor(Color(1.0f, 0.8f, 0.1f));
	left_mat.SetDiffuse(0.7f);
	left_mat.SetSpecular(0.3f);
	left.SetMaterial(left_mat);
	
	PointLight light(Point(-10.0f, 10.0f, -10.0f), Color(1.0f, 1.0f, 1.0f));

	Camera camera(res_x, res_y, utils::kPI / 3.0f);
	camera.SetTransform(Matrix4().view_transform(Point(0.0f, 1.5f, -5.0f),
																							 Point(0.0f, 1.0f, 0.0f),
																							 Vector(0.0f, 1.0f, 0.0f)));

	world.AddObject(&floor);
	world.AddObject(&middle);
	world.AddObject(&right);
	world.AddObject(&left);
	world.AddObject(&light);
	world.AddObject(&camera);

	Canvas image = Engine::render(camera, world);
	
	utils::ExportFile("render_test.ppm", image.ToPPM());

	std::cout << "\n\nPress any key to exit...";
	std::cin.get();
	return 0;
}
