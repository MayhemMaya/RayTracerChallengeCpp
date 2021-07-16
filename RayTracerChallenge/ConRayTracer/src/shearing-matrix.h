#pragma once

#include "matrix4.h"

class ShearingMatrix : public Matrix4 {
 public:
  ShearingMatrix(float x_y, float x_z,
                 float y_x, float y_z,
                 float z_x, float z_y);
};
