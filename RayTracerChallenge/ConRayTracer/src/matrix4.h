#pragma once

#include <iostream>
#include "matrix3.h"
#include "tuple.h"
#include "point.h"

class Matrix3;

class Matrix4 {
 public:
  Matrix4();
  Matrix4(const Matrix4& copy);
  Matrix4(float a11, float a12, float a13, float a14,
          float a21, float a22, float a23, float a24,
          float a31, float a32, float a33, float a34,
          float a41, float a42, float a43, float a44);
  virtual float operator()(unsigned int row, unsigned int col) const;
  virtual void operator()(unsigned int row, unsigned int col, float value);
  friend std::ostream& operator<<(std::ostream& os, const Matrix4& obj);
  bool operator==(const Matrix4& other) const;
  bool operator!=(const Matrix4& other) const;
  Matrix4 operator*(const Matrix4& other) const;
  Tuple operator*(const Tuple& other) const;
  virtual Point operator*(const Point& other) const;
  Matrix4& operator=(const Matrix4& other);
  Matrix4 transpose() const;
  Matrix3 submatrix(int row, int col) const;
  float minor(int row, int col) const;
  float cofactor(int row, int col) const;
  float determinant() const;
  Matrix4 inverse() const;
 private:
  float data_[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  };
  bool invertible() const;
};
