#include <cmath>
#include "rotation-matrix.h"
#include "point.h"
#include "vector.h"

RotationMatrix::RotationMatrix(float x, float y, float z)
    : rotation_x_(1, 0, 0, 0,
                  0, cos(x), -sin(x), 0,
                  0, sin(x),  cos(x), 0,
                  0, 0, 0, 1),
      rotation_y_(cos(y), 0, sin(y), 0,
                  0, 1, 0, 0,
                  -sin(y), 0, cos(y), 0,
                  0, 0, 0, 1),
      rotation_z_(cos(z), -sin(z), 0, 0,
                  sin(z),  cos(z), 0, 0,
                  0, 0, 1, 0,
                  0, 0, 0, 1),
      result_(rotation_x_* rotation_y_* rotation_z_) {}

float RotationMatrix::operator()(unsigned int y, unsigned int x) const {
  return result_(y, x);
}

Point RotationMatrix::operator*(const Point& other) const {
  Point p(0, 0, 0);

  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      float temp = result_(r, 0) * other[0] +
                   result_(r, 1) * other[1] +
                   result_(r, 2) * other[2] +
                   result_(r, 3) * other[3];
      p(r, temp);
    }
  }
  return p;
}

Vector RotationMatrix::operator*(const Vector& other) const {
  Vector v(0, 0, 0);

  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      float temp = result_(r, 0) * other[0] +
                   result_(r, 1) * other[1] +
                   result_(r, 2) * other[2] +
                   result_(r, 3) * other[3];
      v(r, temp);
    }
  }
  return v;
}

Matrix4 RotationMatrix::inverse() const {
  return result_.inverse();
}

