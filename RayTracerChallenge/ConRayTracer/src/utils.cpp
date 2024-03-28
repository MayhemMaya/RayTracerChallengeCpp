
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

  // using structured bindings here now.
  auto [tmin, tmax] = TimeValuePair();

  if (abs(axis_direction) >= utils::kEPSILON) {
    tmin = tmin_numerator / axis_direction;
    tmax = tmax_numerator / axis_direction;
  }
  else {
    tmin = tmin_numerator * utils::kINFINITY;
    tmax = tmax_numerator * utils::kINFINITY;
  }

  if (tmin > tmax) utils::swap(tmin, tmax);

  return { tmin, tmax };
}

std::string remove_all_whitespace(std::string str) {
  str.erase(remove(str.begin(), str.end(), ' '), str.end());
  return str;
}

std::string remove_leading_whitespace(std::string str) {
  std::string::size_type index = str.find_first_not_of(" ");
  if (index == std::string::npos) {
    return str;
  }
  return str.substr(index, str.length());
}

std::string remove_trailing_whitespace(std::string str) {
  std::string::size_type index = str.find_last_not_of(" ");
  return str.substr(0, index + 1);
}

std::string remove_leading_and_trailing_whitespace(std::string str) {
  std::string str1 = remove_leading_whitespace(str);
  return remove_trailing_whitespace(str1);
}

std::string create_equal_whitespace(std::string str) {
  std::string new_str;
  bool found_whitespace = false;
  for (int i = 0; i < str.size(); i++) {
    if (str[i] == ' ' && !found_whitespace) {
      found_whitespace = true;
      new_str += str[i];
    }
    if (str[i] != ' ') {
      found_whitespace = false;
      new_str += str[i];
    }
  }
  return new_str;
}

FileNameCheck check_file_name(std::string file_name, FileExtensions ext) {
  file_name = remove_all_whitespace(file_name);
  FileNameCheck check;
  std::string::size_type period_index = file_name.find_last_of(".");
  if (period_index == std::string::npos) {
    check.err.occured = true;
    check.err.msg = "Error: Filename '" + file_name + "' does not contain period '.' or required extension.";
    return check;
  }

  std::string file_ext = file_name.substr(period_index, file_name.length());
  if (file_ext != extMap[ext]) {
    check.err.occured = true;
    check.err.msg = "Error: Filename '" + file_name + "' does not contain correct extension '" + extMap[ext] + "'.";
    return check;
  }

  check.file_name = file_name;
  return check;
}

SplitStringResult split_string(std::string str, char delimiter) {
  SplitStringResult result;
  result.failed = false;

  std::string::size_type delimiter_index = str.find(delimiter);
  if (delimiter_index == std::string::npos) {
    result.failed = true;
    return result;
  }

  std::string segment;
  std::stringstream ss;
  ss << str;
  while (std::getline(ss, segment, delimiter)) {
    result.segments.push_back(segment);
  }
  return result;
}

Number string_to_number(const std::string& str, bool suppress_errors) {
  Number num;
  num.type = NumberType::UNKNOWN;
  num.float_value = 0.0f;
  num.int_value = 0;

  if (str == "") {
    if (!suppress_errors) std::cerr << "string_to_number(): String is empty!\n";
  }

  std::string::size_type decimal_point_index = str.find_first_of('.');
  if (decimal_point_index != std::string::npos) {
    try {
      num.float_value = std::stof(str);
      num.type = NumberType::FLOAT;
      return num;
    }
    catch (...) {
      if (!suppress_errors) std::cerr << "string_to_number(): String is not a floating point number!\n";
    }
  }

  try {
    num.int_value = std::stoi(str);
    num.type = NumberType::INT;
  }
  catch (...) {
    if (!suppress_errors) std::cerr << "string_to_number(): String is not an integer number!\n";
  }
  return num;
}

} // namespace utils