#pragma once

#include "matrix4.h"

class ScalingMatrix : public Matrix4 {
 public:
  ScalingMatrix(float x, float y, float z);
  //Point operator*(const Point& other) const override;
  //Vector operator*(const Vector& other) const;
};
