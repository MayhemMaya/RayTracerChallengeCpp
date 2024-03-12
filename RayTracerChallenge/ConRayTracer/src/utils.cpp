
#include "utils.h"

namespace utils {
  
bool equal(float a, float b) {
  if (std::abs(a - b) < kEPSILON)
    return true;
  return false;
}

float clamp(float value, float min, float max) {
  if (value > max) return max;
  if (value < min) return min;
  return value;
}

std::vector<std::string> split_lines(const std::string& str) {
  std::istringstream stream(str);
  std::vector<std::string> lines;
  std::string current_line;
  while (std::getline(stream, current_line)) {
    if (!current_line.empty()) {
      lines.push_back(current_line);
    }
  }
  return lines;
}

std::string ToString(float value) {
  std::stringstream ss;
  ss << value;
  return ss.str();
}

void ExportFile(const std::string& file_name, const std::string& contents) {
  std::ofstream file(file_name);
  file << contents;
  file.close();
  std::cout << "Exported file: " << "'" << file_name << "'";
}

void swap(float& a, float& b) {
  float temp = a;
  a = b;
  b = temp;
}

void swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

void swap(double& a, double& b) {
  double temp = a;
  a = b;
  b = temp;
}

float radians(float degrees) {
  return(degrees * kPI / 180.0f);
}

float roundoff(float value, int precision) {
  float pow_10 = pow(10.0f, precision);
  return round(value * pow_10) / pow_10;
}

float map(int value, int in_min, int in_max, float out_min, float out_max)
{
  return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void ClearScreen()
{
  system("cls");
}

bool at_least_one_true(std::vector<bool> booleans) {
  // iterate through all booleans and return true as soon as one is true
  for (bool boolean : booleans) {
    if (boolean) {
      return true;
    }
  }
  // if the loop finished and none were false return false
  return false;
}

// checks to see if the intersection at `t` is within a radius
// of 1 (the radius of your cylinders/cones) from the y axis.

bool check_cylinder_cap(const RayStruct& local_ray, const float& t) {
  const auto x = local_ray.origin[0] + t * local_ray.direction[0];
  const auto z = local_ray.origin[2] + t * local_ray.direction[2];
  return (x * x) + (z * z) <= 1;
}

bool check_cone_cap(const RayStruct& local_ray, const float& t, const float& y) {
  const auto x = local_ray.origin[0] + t * local_ray.direction[0];
  const auto z = local_ray.origin[2] + t * local_ray.direction[2];
  return (x * x) + (z * z) <= abs(y);
}

TimeValuePair check_axis(float axis_origin, float axis_direction, float minimum, float maximum) {
  const auto tmin_numerator = (minimum - axis_origin);
  const auto tmax_numerator = (maximum - axis_origin);

  TimeValuePair pair;

  if (abs(axis_direction) >= utils::kEPSILON) {
    pair.tmin = tmin_numerator / axis_direction;
    pair.tmax = tmax_numerator / axis_direction;
  }
  else {
    pair.tmin = tmin_numerator * utils::kINFINITY;
    pair.tmax = tmax_numerator * utils::kINFINITY;
  }

  if (pair.tmin > pair.tmax) utils::swap(pair.tmin, pair.tmax);

  return pair;
}

} // namespace utils