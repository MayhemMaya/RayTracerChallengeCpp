#pragma once

#include <iostream>
#include <sstream>
#include <cmath>
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
  float operator()(int row, int col) const;
  void operator()(int row, int col, float value);
  friend std::ostream& operator<<(std::ostream& os, const Matrix4& obj);
  bool operator==(const Matrix4& other) const;
  bool operator!=(const Matrix4& other) const;
  Matrix4 operator*(const Matrix4& other) const;
  Tuple operator*(const Tuple& other) const;
  Point operator*(const Point& other) const;
  Matrix4& operator=(const Matrix4& other);
  Matrix4 transpose() const;
  Matrix3 submatrix(int row, int col) const;
  float minor(int row, int col) const;
  float cofactor(int row, int col) const;
  float determinant() const;
  bool invertible() const;
  Matrix4 inverse() const;
  std::string format() const;
  Matrix4 identity() const;
  Matrix4 translation(float x, float y, float z) const;
  Matrix4 scaling(float x, float y, float z) const;
  Matrix4 rotation_x(float radians) const;
  Matrix4 rotation_y(float radians) const;
  Matrix4 rotation_z(float radians) const;
  Matrix4 shearing(float x_y, float x_z, float y_x,
                   float y_z, float z_x, float z_y) const;
  Matrix4 view_transform(const Point& from, const Point& to, const Vector& up) const;
 private:
  float data_[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  };
};
