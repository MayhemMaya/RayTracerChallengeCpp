#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include "vector.h"
#include "tuple.h"
#include "color.h"

namespace utils {

const float kEPSILON = 0.00001f;
static float kPI = 3.14159265358979f;
bool equal(float a, float b);
float dot(Tuple a, Tuple b);
Vector cross(Vector a, Vector b);
Color hadamard_product(Color c1, Color c2);
float clamp(float value, float min, float max);
std::vector<std::string> split_lines(std::string str);
std::string ToString(float value);
void ExportFile(std::string file_name, std::string contents);
void swap(float& a, float& b);
void swap(int& a, int& b);
void swap(double& a, double& b);
float radians(float degrees);
float roundoff(float value, int precision);
float map(int value, int in_min, int in_max, float out_min, float out_max);
void ClearScreen();

} // namespace utils
