#pragma once

#include <cstdlib>
#include <vector>
#include <sstream>
#include <fstream>
#include "vector.h"
#include "tuple.h"
#include "color.h"

namespace utils {

const float kEPSILON = 0.00001;
constexpr auto kPI = 3.141592653589793238;
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

} // namespace utils
