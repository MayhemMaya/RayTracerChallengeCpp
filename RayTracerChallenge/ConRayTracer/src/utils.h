#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include "vector.h"
#include "color.h"

namespace utils {

  // Had to adjust the epsilon value here from 0.0001f to 0.001f due to acne appearing on the image when calculating shadows using is_shadowed()
  // Unit tests may be affected.
static float kEPSILON = 0.001f;
static double kPI = 3.141592653589793;
bool equal(float a, float b);
float dot(const Vector& a, const Vector& b);
Vector cross(const Vector& a, const Vector& b);
Color hadamard_product(const Color& c1, const Color& c2);
float clamp(float value, float min, float max);
std::vector<std::string> split_lines(const std::string& str);
std::string ToString(float value);
void ExportFile(const std::string& file_name, const std::string& contents);
void swap(float& a, float& b);
void swap(int& a, int& b);
void swap(double& a, double& b);
float radians(float degrees);
float roundoff(float value, int precision);
float map(int value, int in_min, int in_max, float out_min, float out_max);
void ClearScreen();

} // namespace utils
