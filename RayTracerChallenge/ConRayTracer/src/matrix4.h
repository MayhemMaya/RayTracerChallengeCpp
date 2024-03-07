#pragma once

#include <iostream>
#include <sstream>
#include <cmath>
#include "matrix3.h"
#include "mock-tuple.h"
#include "point.h"
#include <array>

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
  MockTuple operator*(const MockTuple& other) const;
  Point operator*(const Point& other) const;
  Vector operator*(const Vector& other) const;
  Matrix4& operator=(const Matrix4& other);
  Matrix4 transpose() const;
  Matrix3 submatrix(int row, int col) const;
  float minor(int row, int col) const;
  float cofactor(int row, int col) const;
  float determinant() const;
  bool invertible() const;
  Matrix4 inverse() const;
  std::string format() const;
  Matrix4& identity();
  Matrix4& translation(float x, float y, float z);
  Matrix4& scaling(float x, float y, float z);
  Matrix4& rotation_x(float radians);
  Matrix4& rotation_y(float radians);
  Matrix4& rotation_z(float radians);
  Matrix4& shearing(float x_y, float x_z, float y_x,
                   float y_z, float z_x, float z_y);
  Matrix4 view_transform(const Point& from, const Point& to, const Vector& up) const;
 private:
   std::array<std::array<float, 4>, 4> data_;
};
