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
#include <limits>

namespace utils {

struct RayStruct {
  Point origin;
  Vector direction;
};

struct TimeValuePair {
  float tmin, tmax;
};

// Had to adjust the epsilon value here from 0.0001f to 0.001f due to acne appearing on the image when calculating shadows using is_shadowed()
// Unit tests may be affected.
static float kEPSILON = 0.001f;
static double kPI = 3.141592653589793;
static int kRECURSION_DEPTH = 5;
static bool kUSE_ALL_LIGHTS = false;
static double kINFINITY = std::numeric_limits<double>::infinity();
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
bool check_cylinder_cap(const RayStruct& local_ray, const float& t);
bool check_cone_cap(const RayStruct& local_ray, const float& t, const float& y);
TimeValuePair check_axis(float axis_origin, float axis_direction, float minimum, float maximum);

template <typename Base, typename T>

inline bool instance_of(const T* ptr) {
  return dynamic_cast<const Base*>(ptr) != nullptr;
}

template<class C, typename T>
inline bool contains(C&& c, T t) {
  return std::find(std::begin(c), std::end(c), t) != std::end(c);
};

template <typename T>
bool is_close_to_zero(T x)
{
  return std::abs(x) < std::numeric_limits<T>::epsilon();
}

} // namespace utils
