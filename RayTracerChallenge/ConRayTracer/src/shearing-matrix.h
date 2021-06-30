#ifndef SHEARING_MATRIX_H
#define SHEARING_MATRIX_H

#include "matrix4.h"
#include "point.h"

class ShearingMatrix : public Matrix4 {
 public:
  ShearingMatrix(float x_y, float x_z,
                 float y_x, float y_z,
                 float z_x, float z_y);
};

#endif // SHEARING_MATRIX_H
