#ifndef MATRIX_3_H
#define MATRIX_3_H

#include <iostream>
#include <vector>
#include "matrix2.h"
#include "utils.h"

class Matrix3 {
 public:
  Matrix3();
  Matrix3(float a11, float a12, float a13,
          float a21, float a22, float a23,
          float a31, float a32, float a33);
  float operator()(unsigned int y, unsigned int x) const;
  void operator()(unsigned int y, unsigned int x, float value);
  friend std::ostream& operator<<(std::ostream& os, const Matrix3& obj);
  bool operator==(const Matrix3& other) const;
  bool operator!=(const Matrix3& other) const;
  Matrix2 submatrix(int row, int col) const;
  float minor(int row, int col) const;
  float cofactor(int row, int col) const;
  float determinant() const;
 private:
  float data_[3][3] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
  };
};

#endif // MATRIX_3_H