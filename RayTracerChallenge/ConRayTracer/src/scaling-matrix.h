#ifndef SCALING_MATRIX_H
#define SCALING_MATRIX_H

#include "matrix4.h"
#include "point.h"
#include "vector.h"

class ScalingMatrix : public Matrix4 {
 public:
  ScalingMatrix(float x, float y, float z);
  //Point operator*(const Point& other) const override;
  //Vector operator*(const Vector& other) const;
};

#endif // SCALING_MATRIX_H
