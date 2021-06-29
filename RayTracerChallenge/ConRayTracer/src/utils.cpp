
#include <cstdlib>
#include <sstream>
#include <vector>
#include <fstream>
#include "utils.h"

namespace utils {
  
bool equal(float a, float b) {
  if (std::abs(a - b) < kEPSILON)
    return true;
  return false;
}

float dot(Tuple a, Tuple b) {
  return(a[0] * b[0] +
         a[1] * b[1] +
         a[2] * b[2] +
         a[3] * b[3]);
}

Vector cross(Vector a, Vector b) {
  return Vector(a[1] * b[2] - a[2] * b[1],
                a[2] * b[0] - a[0] * b[2],
                a[0] * b[1] - a[1] * b[0]);
}

Color hadamard_product(Color c1, Color c2) {
  return Color(c1[0] * c2[0], c1[1] * c2[1], c1[2] * c2[2]);
}

float clamp(float value, float min, float max) {
  if (value > max) return max;
  if (value < min) return min;
  return value;
}

std::vector<std::string> split_lines(std::string str) {
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

void ExportFile(std::string file_name, std::string contents) {
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

} // namespace utils