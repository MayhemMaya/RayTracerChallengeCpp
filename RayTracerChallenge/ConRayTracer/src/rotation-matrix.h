#pragma once

#include <cmath>
#include "matrix4.h"
#include "point.h"
#include "vector.h"

class RotationMatrix : public Matrix4 {
 public:
  RotationMatrix(float x, float y, float z);
  RotationMatrix operator*(const Matrix4& other) const;
  Point operator*(const Point& other) const override;
  Vector operator*(const Vector& other) const;
  Matrix4 inverse() const;
 private:
  Matrix4 rotation_x_, rotation_y_, rotation_z_, result_;
  float operator()(unsigned int row, unsigned int col) const override;
  void operator()(unsigned int row, unsigned int col, float value) override;
};
