#ifndef UTILS_H
#define UTILS_H

#include "tuple.h"
#include "vector.h"

namespace utils {

const float kEPSILON = 0.00001;
bool equal(float a, float b);
float dot(Tuple a, Tuple b);
Vector cross(Vector a, Vector b);

} // namespace utils

#endif // UTILS_H
