// main.cpp : This file contains the 'main' function. Program execution begins and ends here.
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "ray-tracer.h"

void SpheresScene(int res_x, int res_y) {
	CheckerPattern checker = CheckerPattern(Colors::Black, Colors::White);
	checker.SetTransform(Matrix4().scaling(0.125, 0.125, 0.125));

	World world = World(WorldType::EMPTY);

	Plane floor("floor", Matrix4().scaling(10.0f, 1.0f, 10.0f));
	Material floor_mat;
	floor_mat.SetPattern(&checker);
	floor_mat.SetSpecular(1.0f);
	floor_mat.SetReflectivity(0.25f);
	floor.SetMaterial(floor_mat);

	Plane back_wall("back_wall", Matrix4().translation(0, 0, 2.5).scaling(10.0f, 10.0f, 1.0f).rotation_x(utils::radians(90)));
	Material back_wall_mat;
	back_wall_mat.SetPattern(&checker);
	back_wall_mat.SetSpecular(0.5f);
	back_wall.SetMaterial(back_wall_mat);

	Sphere middle("middle", Matrix4().translation(-0.5f, 1.0f, 0.5f));
	 Material middle_mat;
	 middle_mat.SetColor(Colors::Aqua);
	 middle_mat.SetSpecular(1.0f);
	 middle_mat.SetShininess(200.0f);
	 middle_mat.SetReflectivity(0.0f);
	 middle.SetMaterial(middle_mat);

	Sphere right = Sphere("right", Matrix4().translation(1.5f, 0.5f, -0.5f).scaling(0.5f, 0.5f, 0.5f));
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

	PointLight light("light", Point(0.0f, 5.0f, -5.0f), Colors::White);

	Camera camera("Camera", res_x, res_y, utils::kPI / 3.0f);
	camera.SetTransform(Matrix4().view_transform(Point(0.0f, 2.5f, -10.0f),
																							 Point(0.0f, 0.0f, 0.0f),
																							 Vector(0.0f, 1.0f, 0.0f)));
	
	world.AddObject(&floor);
	world.AddObject(&back_wall);
	world.AddObject(&middle);
	world.AddObject(&right);
	world.AddObject(&left);
	world.AddObject(&light);
	world.AddObject(&camera);

	Canvas image = Engine::render(camera, world);

	image.ExportAsPPM("renders\\spheres.ppm");
}

void CubesScene(int res_x, int res_y) {
	CheckerPattern checker = CheckerPattern(Colors::Black, Colors::White);
	checker.SetTransform(Matrix4().scaling(0.125, 0.125, 0.125));

	World world = World(WorldType::EMPTY);

	Plane floor("floor", Matrix4().scaling(10.0f, 1.0f, 10.0f));
	Material floor_mat;
	floor_mat.SetPattern(&checker);
	floor_mat.SetSpecular(1.0f);
	floor_mat.SetReflectivity(0.25f);
	floor.SetMaterial(floor_mat);

	Plane back_wall("back_wall", Matrix4().translation(0, 0, 2.5).scaling(10.0f, 10.0f, 1.0f).rotation_x(utils::radians(90)));
	Material back_wall_mat;
	back_wall_mat.SetPattern(&checker);
	back_wall_mat.SetSpecular(0.5f);
	back_wall.SetMaterial(back_wall_mat);

	Material cube_mat;
	cube_mat.SetColor(Color(0.05f, 0.7f, 1.0f));

	Cube cube1 = Cube("cube", Matrix4().translation(-0.725, 0.5, 0).scaling(0.25f, 0.25f, 0.25f));
	Cube cube2 = Cube("cube", Matrix4().translation(0, 0.5, 0).scaling(0.25f, 0.25f, 0.25f));
	Cube cube3 = Cube("cube", Matrix4().translation(0.725, 0.5, 0).scaling(0.25f, 0.25f, 0.25f));
	Cube cube4 = Cube("cube", Matrix4().translation(-0.3625, 1, 0).scaling(0.25f, 0.25f, 0.25f));
	Cube cube5 = Cube("cube", Matrix4().translation(0.3625, 1, 0).scaling(0.25f, 0.25f, 0.25f));
	Cube cube6 = Cube("cube", Matrix4().translation(0, 1.5, 0).scaling(0.25f, 0.25f, 0.25f));

	Group cube_group = Group("cube_group");
	cube_group.SetTransform(Matrix4().translation(0, 0, -1.75));
	cube_group.SetMaterial(cube_mat);
	cube_group.AddChild(&cube1);
	cube_group.AddChild(&cube2);
	cube_group.AddChild(&cube3);
	cube_group.AddChild(&cube4);
	cube_group.AddChild(&cube5);
	cube_group.AddChild(&cube6);

	PointLight light("light", Point(0.0f, 5.0f, -5.0f), Colors::White);

	Camera camera("Camera", res_x, res_y, utils::kPI / 3.0f);
	camera.SetTransform(Matrix4().view_transform(Point(0.0f, 2.5f, -10.0f),
		Point(0.0f, 0.0f, 0.0f),
		Vector(0.0f, 1.0f, 0.0f)));

	world.AddObject(&floor);
	world.AddObject(&back_wall);
	world.AddObject(&cube_group);
	world.AddObject(&light);
	world.AddObject(&camera);

	Canvas image = Engine::render(camera, world);

	image.ExportAsPPM("renders\\cubes.ppm");
}

void HexagonScene(int res_x, int res_y) {

	World world = World(WorldType::EMPTY);

	Material blue_mat;
	blue_mat.SetColor(Color(0.05f, 0.7f, 1.0f));
	blue_mat.SetDiffuse(0.7f);
	blue_mat.SetSpecular(0.3f);

	Hexagon hex = Hexagon("hex", blue_mat);

	PointLight light("light", Point(0.0f, 5.0f, -5.0f), Colors::White);

	Camera camera("Camera", res_x, res_y, utils::kPI / 3.0f);
	camera.SetTransform(Matrix4().view_transform(Point(0.0f, 2.0f, -2.5f),
																							 Point(0.0f, 0.0f, 0.0f),
																							 Vector(0.0f, 1.0f, 0.0f)));
									
	world.AddObject(&light);
	world.AddObject(&hex);
	world.AddObject(&camera);

	Canvas image = Engine::render(camera, world);

	image.ExportAsPPM("renders\\hexagon.ppm");
}

void ObjTeapotScene(int res_x, int res_y) {

	World world = World(WorldType::EMPTY);

	Material teapot_mat;
	teapot_mat.SetColor(Colors::Purple);

	CheckerPattern checker = CheckerPattern(Color(0.8, 0.8, 0.8), Color(0.7, 0.7, 0.7));
	checker.SetTransform(Matrix4().scaling(0.125, 0.125, 0.125));

	Material checker_mat;
	checker_mat.SetPattern(&checker);
	//checker_mat.SetSpecular(1.0f);
	//checker_mat.SetReflectivity(0.25f);

	Plane floor("floor", Matrix4().scaling(10.0f, 1.0f, 10.0f));
	floor.SetMaterial(checker_mat);

	Plane back_wall("back_wall", Matrix4().translation(0, 0, -15).scaling(10.0f, 10.0f, 1.0f).rotation_x(utils::radians(90)));
	back_wall.SetMaterial(checker_mat);

	/*ObjParser Teapot_low_parser = ObjParser("obj_files\\teapot_low.obj", ShadingType::SMOOTH);
	Group* teapot_low = new Group("teapot_low_poly");
	teapot_low->SetTransform(Matrix4().scaling(0.5, 0.5, 0.5).rotation_x(utils::radians(-45)));
	teapot_low->SetMaterial(teapot_mat);
	Teapot_low_parser.ConvertToSceneGroup(teapot_low);*/

	ObjParser Teapot_high_parser = ObjParser("obj_files\\teapot_high.obj", ShadingType::SMOOTH);
	Group* teapot_high = new Group("teapot_high_poly");
	teapot_high->SetTransform(Matrix4().scaling(0.5, 0.5, 0.5).rotation_x(utils::radians(-45)));
	teapot_high->SetMaterial(teapot_mat);
	Teapot_high_parser.ConvertToSceneGroup(teapot_high);

	PointLight light("light", Point(-2.0f, 4.0f, 4.0f), Colors::White);

	Camera camera("Camera", res_x, res_y, utils::kPI / 3.0f);
	camera.SetTransform(Matrix4().view_transform(Point(0.0f, 5.0f, 9.0f),
		Point(0.0f, 1.5f, 0.0f),
		Vector(0.0f, 1.0f, 0.0f)));

	world.AddObject(&light);
	world.AddObject(&floor);
	world.AddObject(&back_wall);
	world.AddObject(teapot_high);
	world.AddObject(&camera);

	Canvas image = Engine::render(camera, world);

	image.ExportAsPPM("renders\\teapot.ppm");
}

void CSGScene(int res_x, int res_y) {
	Material mirror;
	mirror.SetAmbient(0.0f);
	mirror.SetDiffuse(0.0f);
	mirror.SetSpecular(1.0f);
	mirror.SetShininess(200.0f);
	mirror.SetReflectivity(1.0f);

	CheckerPattern checker = CheckerPattern(Colors::Black, Colors::White);
	checker.SetTransform(Matrix4().scaling(0.125, 0.125, 0.125));

	World world = World(WorldType::EMPTY);

	Material checker_mat;
	checker_mat.SetPattern(&checker);
	checker_mat.SetSpecular(1.0f);

	Plane floor("floor", Matrix4().scaling(10.0f, 1.0f, 10.0f));
	floor.SetMaterial(checker_mat);
	floor.SetCanOptOutOfShadow(true);

	Plane ceiling("ceiling", Matrix4().scaling(10.0f, 1.0f, 10.0f).rotation_x(utils::radians(180)).translation(0, 20, 0));
	ceiling.SetMaterial(checker_mat);

	Plane back_wall("back_wall", Matrix4().translation(0, 0, 20).scaling(10.0f, 10.0f, 1.0f).rotation_x(utils::radians(90)));
	back_wall.SetMaterial(checker_mat);

	Plane front_wall("front_wall", Matrix4().translation(0, 0, -20).scaling(10.0f, 10.0f, 1.0f).rotation_x(utils::radians(-90)));
	front_wall.SetMaterial(checker_mat);

	Sphere middle("middle", Matrix4().translation(0, 1.5f, -5));
	middle.SetMaterial(mirror);

	Cylinder c1 = Cylinder("c1", -5, 5, true);
	c1.SetTransform(Matrix4().translation(0, 1.5f, -5).scaling(0.5, 0.5, 0.5));
	c1.SetCanOptOutOfShadow(true);

	Cylinder c2 = Cylinder("c1", -5, 5, true);
	c2.SetTransform(Matrix4().translation(0, 1.5f, -5).scaling(0.5, 0.5, 0.5).rotation_x(utils::radians(90)));
	c2.SetCanOptOutOfShadow(true);

	Cylinder c3 = Cylinder("c1", -5, 5, true);
	c3.SetTransform(Matrix4().translation(0, 1.5f, -5).scaling(0.5, 0.5, 0.5).rotation_z(utils::radians(90)));
	c3.SetCanOptOutOfShadow(true);

	Material transparent_mat;
	transparent_mat.SetTransparency(1.0f);
	transparent_mat.SetAmbient(0.0f);
	transparent_mat.SetDiffuse(0.0f);
	transparent_mat.SetRefractiveIndex(0.0f);
	transparent_mat.SetReflectivity(1.0f);
	transparent_mat.SetReflectivity(1.0f);
	transparent_mat.SetShininess(200.0f);

	Group g = Group("cylinder_group");
	g.SetMaterial(transparent_mat);
	g.SetCanOptOutOfShadow(true);
	g.AddChild(&c1);
	g.AddChild(&c2);
	g.AddChild(&c3);

	CSG csg = CSG(Operation::DIFFERENCE, &middle, &g);

	PointLight light1("light1", Point(20.0f, 5.0f, -5.0f), Colors::Blue);
	PointLight light2("light2", Point(-20.0f, 5.0f, -5.0f), Colors::HotPink);

	Camera camera("Camera", res_x, res_y, utils::kPI / 3.0f);
	camera.SetTransform(Matrix4().view_transform(Point(0.0f, 2.5f, -10.0f),
		Point(0.0f, 0.0f, 0.0f),
		Vector(0.0f, 1.0f, 0.0f)));

	world.AddObject(&floor);
	world.AddObject(&ceiling);
	world.AddObject(&back_wall);
	world.AddObject(&front_wall);
	world.AddObject(&csg);
	world.AddObject(&light1);
	world.AddObject(&light2);
	world.AddObject(&camera);

	Canvas image = Engine::render(camera, world);

	image.ExportAsPPM("renders\\csg.ppm");
}

void CoverImageScene(int res_x, int res_y) {
	// Empty world
	World world = World(WorldType::EMPTY);

	// Camera
	Camera camera("Camera", res_x, res_y, 0.785f);
	camera.SetTransform(Matrix4().view_transform(Point(-6, 6, -10),
																							 Point(6, 0, 6),
																							 Vector(-0.45f, 1, 0)));

	// Light Sources
	PointLight light1("light1", Point(50, 100, -50), Color(1, 1, 1));
	PointLight light2("light2", Point(-400, 50, -10), Color(0.2f, 0.2f, 0.2f));

	// Commonly used materials
	Material white_mat;
	white_mat.SetColor(Color(1, 1, 1));
	white_mat.SetDiffuse(0.7f);
	white_mat.SetAmbient(0.1f);
	white_mat.SetSpecular(0.0f);
	white_mat.SetReflectivity(0.1f);

	Material blue_mat = Material(white_mat);
	blue_mat.SetColor(Color(0.537f, 0.831f, 0.914f));

	Material red_mat = Material(white_mat);
	red_mat.SetColor(Color(0.941f, 0.322f, 0.388f));

	Material purple_mat = Material(white_mat);
	purple_mat.SetColor(Color(0.373f, 0.404f, 0.550f));

	// Commonly used transformations
	Matrix4 standard_transform = Matrix4().scaling(0.5f, 0.5, 0.5f).translation(1, -1, 1);

	Matrix4 large_object = Matrix4().scaling(3.5f, 3.5f, 3.5f);
	large_object = large_object * standard_transform;

	Matrix4 medium_object = Matrix4().scaling(3, 3, 3);
	medium_object = medium_object * standard_transform;

	Matrix4 small_object = Matrix4().scaling(2, 2, 2);
	small_object = small_object * standard_transform;

	// Scene objects
	Material plane_mat;
	plane_mat.SetColor(Color(1, 1, 1));
	plane_mat.SetAmbient(1.0f);
	plane_mat.SetDiffuse(0.0f);
	plane_mat.SetSpecular(0.0f);

	Plane backdrop = Plane("backdrop", plane_mat, Matrix4().translation(0, 0, 500).rotation_x(utils::kPI / 2));

	Material sphere_mat;
	sphere_mat.SetColor(Color(0.373f, 0.404f, 0.550f));
	sphere_mat.SetDiffuse(0.2f);
	sphere_mat.SetAmbient(0.0f);
	sphere_mat.SetSpecular(1.0f);
	sphere_mat.SetShininess(200.0f);
	sphere_mat.SetReflectivity(0.7f);
	sphere_mat.SetTransparency(0.7f);
	sphere_mat.SetRefractiveIndex(1.5f);

	Sphere sphere = Sphere("sphere", sphere_mat, large_object);

	Cube cube1 = Cube("cube1", white_mat, Matrix4().translation(4, 0, 0) * medium_object);
	Cube cube2 = Cube("cube2", blue_mat, Matrix4().translation(8.5f, 1.5f, -0.5f) * large_object);
	Cube cube3 = Cube("cube3", red_mat, Matrix4().translation(0, 0, 4) * large_object);
	Cube cube4 = Cube("cube4", white_mat, Matrix4().translation(4, 0, 4) * small_object);
	Cube cube5 = Cube("cube5", purple_mat, Matrix4().translation(7.5f, 0.5f, 4) * medium_object);
	Cube cube6 = Cube("cube6", white_mat, Matrix4().translation(-0.25f, 0.25f, 8) * medium_object);
	Cube cube7 = Cube("cube7", blue_mat, Matrix4().translation(4, 1, 7.5f) * large_object);
	Cube cube8 = Cube("cube8", red_mat, Matrix4().translation(10, 2, 7.5f) * medium_object);
	Cube cube9 = Cube("cube9", white_mat, Matrix4().translation(8, 2, 12) * small_object);
	Cube cube10 = Cube("cube10", white_mat, Matrix4().translation(20, 1, 9) * small_object);
	Cube cube11 = Cube("cube11", blue_mat, Matrix4().translation(-0.5f, -5, 0.25f) * large_object);
	Cube cube12 = Cube("cube12", red_mat, Matrix4().translation(4, -4, 0) * large_object);
	Cube cube13 = Cube("cube13", white_mat, Matrix4().translation(8.5f, -4, 0) * large_object);
	Cube cube14 = Cube("cube14", white_mat, Matrix4().translation(0, -4, 4) * large_object);
	Cube cube15 = Cube("cube15", purple_mat, Matrix4().translation(-0.5f, -4.5f, 8) * large_object);
	Cube cube16 = Cube("cube16", white_mat, Matrix4().translation(0, -8, 4) * large_object);
	Cube cube17 = Cube("cube17", white_mat, Matrix4().translation(-0.5f, -8.5f, 8) * large_object);

	world.AddObject(&camera);
	world.AddObject(&light1);
	world.AddObject(&light2);
	world.AddObject(&backdrop);
	world.AddObject(&sphere);
	world.AddObject(&cube1);
	world.AddObject(&cube2);
	world.AddObject(&cube3);
	world.AddObject(&cube4);
	world.AddObject(&cube5);
	world.AddObject(&cube6);
	world.AddObject(&cube7);
	world.AddObject(&cube8);
	world.AddObject(&cube9);
	world.AddObject(&cube10);
	world.AddObject(&cube11);
	world.AddObject(&cube12);
	world.AddObject(&cube13);
	world.AddObject(&cube14);
	world.AddObject(&cube15);
	world.AddObject(&cube16);
	world.AddObject(&cube17);

	Canvas image = Engine::render(camera, world);

	image.ExportAsPPM("renders\\cover_image.ppm");
}

int main() {

	int res_x = 800;
	int res_y = 400;

	//SpheresScene(res_x, res_y);
	//CubesScene(res_x, res_y);
	//HexagonScene(res_x, res_y);
	//ObjTeapotScene(res_x, res_y);
	//CSGScene(res_x, res_y);
	CoverImageScene(1024, 1024);

	std::cout << "\n\nPress any key to exit...";
	std::cin.get();
	
	return 0;
}
