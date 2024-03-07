#pragma once

#include <iostream>
#include <vector>
#include "matrix2.h"
#include<array>

class Matrix3 {
 public:
  Matrix3();
  Matrix3(float a11, float a12, float a13,
          float a21, float a22, float a23,
          float a31, float a32, float a33);
  float operator()(int y, int x) const;
  void operator()(int y, int x, float value);
  friend std::ostream& operator<<(std::ostream& os, const Matrix3& obj);
  bool operator==(const Matrix3& other) const;
  bool operator!=(const Matrix3& other) const;
  Matrix2 submatrix(int row, int col) const;
  float minor(int row, int col) const;
  float cofactor(int row, int col) const;
  float determinant() const;
 private:
  std::array<std::array<float, 3>, 3> data_;
};
