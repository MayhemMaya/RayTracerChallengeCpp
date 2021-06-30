#include "shearing-matrix.h"

ShearingMatrix::ShearingMatrix(float x_y, float x_z,
                               float y_x, float y_z,
                               float z_x, float z_y)
    : Matrix4(1, x_y, x_z, 0,
              y_x, 1, y_z, 0,
              z_x, z_y, 1, 0,
              0, 0, 0, 1) {}