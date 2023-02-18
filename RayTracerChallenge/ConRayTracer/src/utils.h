#pragma once

#include <cstdlib>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include "vector.h"
#include "point.h"
#include <cmath>
#include <algorithm>

namespace utils {

  // Had to adjust the epsilon value here from 0.0001f to 0.001f due to acne appearing on the image when calculating shadows using is_shadowed()
  // Unit tests may be affected.
static float kEPSILON = 0.001f;
static double kPI = 3.141592653589793;
static int kRECURSION_DEPTH = 5;
static bool kUSE_ALL_LIGHTS = false;
bool equal(float a, float b);
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
bool at_least_one_true(std::vector<bool> booleans);

struct RayStruct {
  Point origin;
  Vector direction;
};

template <typename Base, typename T>

inline bool instance_of(const T* ptr) {
  return dynamic_cast<const Base*>(ptr) != nullptr;
}

template<class C, typename T>
inline bool contains(C&& c, T t) {
  return std::find(std::begin(c), std::end(c), t) != std::end(c);
};

} // namespace utils
