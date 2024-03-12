// main.cpp : This file contains the 'main' function. Program execution begins and ends here.
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "ray-tracer.h"

void SpheresScene(int res_x, int res_y) {
	Material mirror;
	mirror.SetAmbient(0.0f);
	mirror.SetDiffuse(0.0f);
	mirror.SetSpecular(1.0f);
	mirror.SetShininess(200.0f);
	mirror.SetReflectivity(1.0f);

	CheckerPattern checker1 = CheckerPattern(Colors::Black, Colors::White);
	CheckerPattern checker2 = CheckerPattern(Colors::Black, Colors::White);
	checker1.SetTransform(Matrix4().scaling(0.125, 0.125, 0.125));
	checker2.SetTransform(Matrix4().scaling(0.125, 0.125, 0.125));

	World world = World(WorldType::EMPTY);

	Plane floor("floor", Matrix4().scaling(10.0f, 1.0f, 10.0f));
	Material floor_mat;
	floor_mat.SetPattern(&checker2);
	floor_mat.SetSpecular(1.0f);
	floor_mat.SetReflectivity(0.25f);
	floor.SetMaterial(floor_mat);

	Plane back_wall("back_wall", Matrix4().translation(0, 0, 2.5).scaling(10.0f, 10.0f, 1.0f).rotation_x(utils::radians(90)));
	Material back_wall_mat;
	back_wall_mat.SetPattern(&checker1);
	back_wall_mat.SetSpecular(0.5f);
	back_wall.SetMaterial(back_wall_mat);
	// Plane front_wall("front_wall", Matrix4().translation(0, 0, -5).scaling(10.0f, 0.01f, 10.0f).rotation_x(utils::radians(-90)));
	// front_wall.SetMaterial(mirror);

	Sphere middle("middle", Matrix4().translation(-0.5f, 1.0f, 0.5f));
	// Material middle_mat;
	// middle_mat.SetColor(Colors::DarkRed);
	// middle_mat.SetSpecular(1.0f);
	// middle_mat.SetShininess(200.0f);
	// middle_mat.SetReflectivity(0.0f);
	middle.SetMaterial(mirror);

	Sphere right = Sphere("right", Matrix4().translation(1.5f, 0.5f, -0.5f).scaling(0.5f, 0.5f, 0.5f));
	/*right.GetMaterial().SetShininess(1000.0f);
	right.GetMaterial().SetSpecular(0.0f);
	right.GetMaterial().SetTransparency(1.0f);
	right.GetMaterial().SetDiffuse(0.0f);
	right.GetMaterial().SetReflectivity(0.9f);
	right.GetMaterial().SetAmbient(0.0f);
	right.GetMaterial().SetRefractiveIndex(1.5f);*/
	Material right_mat;
	right_mat.SetColor(Color(0.5f, 1.0f, 0.1f));
	right_mat.SetDiffuse(0.7f);
	right_mat.SetSpecular(0.3f);
	right.SetMaterial(right_mat);

	Sphere left = Sphere("left", Matrix4().translation(-1.5f, 0.33f, -0.75f).scaling(0.33f, 0.33f, 0.33f));
	Material left_mat;
	left_mat.SetColor(Color(1.0f, 0.8f, 0.1f));
	left_mat.SetDiffuse(0.7f);
	left_mat.SetSpecular(0.3f);
	left.SetMaterial(left_mat);

	Cube cube1 = Cube("Cube1", Matrix4().translation(0.5f, 0.5f, -0.75f).scaling(0.25f, 0.25f, 0.25f).rotation_x(45).rotation_y(45).rotation_z(45));
	Material cube1_mat;
	cube1_mat.SetColor(Color(0.05f, 0.7f, 1.0f));
	cube1_mat.SetDiffuse(0.7f);
	cube1_mat.SetSpecular(0.3f);
	cube1.SetMaterial(cube1_mat);

	//PointLight light(Point(-10.0f, 10.0f, -10.0f), Color(1.0f, 1.0f, 1.0f));
	//PointLight light(Point(-5.0f, 10.0f, 0.0f), Color(1.0f, 1.0f, 1.0f));
	PointLight light("PointLight", Point(0.0f, 5.0f, -5.0f), Colors::White);
	//PointLight light1("red_light", Point(-10.0f, 5.0f, -5.0f), Colors::Red);
	//PointLight light2("green_light", Point(0.0f, 5.0f, -5.0f), Colors::Green);
	//PointLight light3("blue_light", Point(10.0f, 5.0f, -5.0f), Colors::Blue);

	Camera camera("Camera", res_x, res_y, utils::kPI / 3.0f);
	camera.SetTransform(Matrix4().view_transform(Point(0.0f, 2.5f, -10.0f),
																							 Point(0.0f, 0.0f, 0.0f),
																							 Vector(0.0f, 1.0f, 0.0f)));
	
	world.AddObject(&floor);
	world.AddObject(&back_wall);
	// world.AddObject(&front_wall);
	world.AddObject(&middle);
	world.AddObject(&right);
	world.AddObject(&left);
	world.AddObject(&light);
	//world.AddObject(&cube1);
	// world.AddObject(&light1);
	// world.AddObject(&light2);
	// world.AddObject(&light3);
	world.AddObject(&camera);

	Canvas image = Engine::render(camera, world);

	utils::ExportFile("spheres.ppm", image.ToPPM());
}

void HexagonScene(int res_x, int res_y) {

	World world = World(WorldType::EMPTY);

	Material blue_mat;
	blue_mat.SetColor(Color(0.05f, 0.7f, 1.0f));
	blue_mat.SetDiffuse(0.7f);
	blue_mat.SetSpecular(0.3f);

	Hexagon hex = Hexagon("hex", blue_mat);

	PointLight light("PointLight", Point(0.0f, 5.0f, -5.0f), Colors::White);

	Camera camera("Camera", res_x, res_y, utils::kPI / 3.0f);
	camera.SetTransform(Matrix4().view_transform(Point(0.0f, 2.0f, -2.5f),
																							 Point(0.0f, 0.0f, 0.0f),
																							 Vector(0.0f, 1.0f, 0.0f)));
									
	world.AddObject(&light);
	world.AddObject(&hex);
	world.AddObject(&camera);

	Canvas image = Engine::render(camera, world);

	utils::ExportFile("hexagon.ppm", image.ToPPM());
}

int main() {

	int res_x = 400;
	int res_y = 200;

	//SpheresScene(res_x, res_y);
	HexagonScene(res_x, res_y);

	std::cout << "\n\nPress any key to exit...";
	std::cin.get();
	
	return 0;
}
