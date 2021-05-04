
#include <cstdlib>
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

} // namespace utils