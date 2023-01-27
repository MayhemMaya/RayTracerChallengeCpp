#include <iostream>
#include <sstream>
#include <cmath>
#include "matrix4.h"
#include "matrix3.h"
#include "mock-tuple.h"
#include "point.h"

Matrix4::Matrix4() {}

Matrix4::Matrix4(const Matrix4& copy) {
  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      data_[r][c] = copy(r, c);
    }
  }
}

Matrix4::Matrix4(float a11, float a12, float a13, float a14,
                 float a21, float a22, float a23, float a24,
                 float a31, float a32, float a33, float a34,
                 float a41, float a42, float a43, float a44) {
  data_[0][0] = a11;
  data_[0][1] = a12;
  data_[0][2] = a13;
  data_[0][3] = a14;
  data_[1][0] = a21;
  data_[1][1] = a22;
  data_[1][2] = a23;
  data_[1][3] = a24;
  data_[2][0] = a31;
  data_[2][1] = a32;
  data_[2][2] = a33;
  data_[2][3] = a34;
  data_[3][0] = a41;
  data_[3][1] = a42;
  data_[3][2] = a43;
  data_[3][3] = a44;
}

float Matrix4::operator()(int row, int col) const {
  return data_[row][col];
}

void Matrix4::operator()(int row, int col, float value) {
  data_[row][col] = value;
}

std::ostream& operator<<(std::ostream& os, const Matrix4& obj) {
  for (int r = 0; r < 4; r++) {
    os << "[";
    for (int c = 0; c < 4; c++) {
      if (c < 3)
        os << obj(r, c) << ", ";
      else os << obj(r, c);
    }
    os << "]" << std::endl;
  }
  return os;
}

bool Matrix4::operator==(const Matrix4& other) const {
  return(utils::equal(data_[0][0], other(0, 0)) &&
         utils::equal(data_[0][1], other(0, 1)) &&
         utils::equal(data_[0][2], other(0, 2)) &&
         utils::equal(data_[0][3], other(0, 3)) &&
         utils::equal(data_[1][0], other(1, 0)) &&
         utils::equal(data_[1][1], other(1, 1)) &&
         utils::equal(data_[1][2], other(1, 2)) &&
         utils::equal(data_[1][3], other(1, 3)) &&
         utils::equal(data_[2][0], other(2, 0)) &&
         utils::equal(data_[2][1], other(2, 1)) &&
         utils::equal(data_[2][2], other(2, 2)) &&
         utils::equal(data_[2][3], other(2, 3)) &&
         utils::equal(data_[3][0], other(3, 0)) &&
         utils::equal(data_[3][1], other(3, 1)) &&
         utils::equal(data_[3][2], other(3, 2)) &&
         utils::equal(data_[3][3], other(3, 3)));
}

bool Matrix4::operator!=(const Matrix4& other) const {
  return(!utils::equal(data_[0][0], other(0, 0)) &&
         !utils::equal(data_[0][1], other(0, 1)) &&
         !utils::equal(data_[0][2], other(0, 2)) &&
         !utils::equal(data_[0][3], other(0, 3)) &&
         !utils::equal(data_[1][0], other(1, 0)) &&
         !utils::equal(data_[1][1], other(1, 1)) &&
         !utils::equal(data_[1][2], other(1, 2)) &&
         !utils::equal(data_[1][3], other(1, 3)) &&
         !utils::equal(data_[2][0], other(2, 0)) &&
         !utils::equal(data_[2][1], other(2, 1)) &&
         !utils::equal(data_[2][2], other(2, 2)) &&
         !utils::equal(data_[2][3], other(2, 3)) &&
         !utils::equal(data_[3][0], other(3, 0)) &&
         !utils::equal(data_[3][1], other(3, 1)) &&
         !utils::equal(data_[3][2], other(3, 2)) &&
         !utils::equal(data_[3][3], other(3, 3)));
}

Matrix4 Matrix4::operator*(const Matrix4& other) const {
  Matrix4 M;

  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      float temp = data_[r][0] * other(0, c) +
                   data_[r][1] * other(1, c) +
                   data_[r][2] * other(2, c) +
                   data_[r][3] * other(3, c);
      M(r, c, temp);
    }
  }
  return M;
}

MockTuple Matrix4::operator*(const MockTuple& other) const {
  MockTuple t;

  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      float temp = data_[r][0] * other[0] +
                   data_[r][1] * other[1] + 
                   data_[r][2] * other[2] + 
                   data_[r][3] * other[3];
      t(r, temp);
    }
  }
  return t;
}

Point Matrix4::operator*(const Point& other) const {
  Point p(0, 0, 0);

  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      float temp = data_[r][0] * other[0] +
                   data_[r][1] * other[1] +
                   data_[r][2] * other[2] +
                   data_[r][3] * other[3];
      p(r, temp);
    }
  }
  return p;
}

Vector Matrix4::operator*(const Vector& other) const {
  Vector v(0, 0, 0);

  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      float temp = data_[r][0] * other[0] +
        data_[r][1] * other[1] +
        data_[r][2] * other[2] +
        data_[r][3] * other[3];
      v(r, temp);
    }
  }
  return v;
}

Matrix4& Matrix4::operator=(const Matrix4& other) {
  if (this != &other) {
    for (int r = 0; r < 4; r++) {
      for (int c = 0; c < 4; c++) {
        this->data_[r][c] = other(r, c);
      }
    }
  }
  return *this;
}

Matrix4 Matrix4::transpose() const {
  Matrix4 M;
  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      M(c, r, data_[r][c]);
    }
  }
  return M;
}

Matrix3 Matrix4::submatrix(int row, int col) const {
  std::vector<float> temps;
  for (int r = 0; r < 4; r++) {
    if (r == row) continue;
    for (int c = 0; c < 4; c++) {
      if (c == col) continue;
      temps.push_back(data_[r][c]);
    }
  }
  
  Matrix3 M;
  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      int i = 3 * r + c;
      M(r, c, temps[i]);
    }
  }
  return M;
}

float Matrix4::minor(int row, int col) const {
  Matrix3 M = this->submatrix(row, col);
  return M.determinant();
}

float Matrix4::cofactor(int row, int col) const {
  float minor = this->minor(row, col);
  if ((row + col) % 2 == 1)
    return -minor;
  return minor;
}

float Matrix4::determinant() const {
  float det = data_[0][0] * cofactor(0, 0) +
              data_[0][1] * cofactor(0, 1) +
              data_[0][2] * cofactor(0, 2) +
              data_[0][3] * cofactor(0, 3);
  return det;
}

bool Matrix4::invertible() const {
  if (this->determinant() == 0)
    return false;
  return true;
}

Matrix4 Matrix4::inverse() const {
  if (!this->invertible()) {
    return *this;
  }

  Matrix4 M;
  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      float cofactor = this->cofactor(r, c);
      M(c, r, cofactor / this->determinant());
    }
  }
  return M;
}

std::string Matrix4::format() const {
  std::stringstream ss;
  for (int r = 0; r < 4; r++) {
    ss << "[";
    for (int c = 0; c < 4; c++) {
      if (c < 3)
        ss << (*this)(r, c) << ", ";
      else ss << (*this)(r, c);
    }
    ss << "]" << std::endl;
  }
  return ss.str();
}

Matrix4 Matrix4::identity() const {
  return *this;
}

Matrix4 Matrix4::translation(float x, float y, float z) const {
  Matrix4 current = *this;
  Matrix4 translation = current * Matrix4(1, 0, 0, x,
                                          0, 1, 0, y,
                                          0, 0, 1, z,
                                          0, 0, 0, 1);
  return translation;
}

Matrix4 Matrix4::scaling(float x, float y, float z) const {
  Matrix4 current = *this;
  Matrix4 scaling = current * Matrix4(x, 0, 0, 0,
                                      0, y, 0, 0,
                                      0, 0, z, 0,
                                      0, 0, 0, 1);
  return scaling;
}

Matrix4 Matrix4::rotation_x(float radians) const {
  Matrix4 current = *this;
  Matrix4 rotation_x = current * Matrix4(1, 0, 0, 0,
                                         0, cos(radians), -sin(radians), 0,
                                         0, sin(radians), cos(radians), 0,
                                         0, 0, 0, 1);
  return rotation_x;
}

Matrix4 Matrix4::rotation_y(float radians) const {
  Matrix4 current = *this;
  Matrix4 rotation_y = current * Matrix4(cos(radians), 0, sin(radians), 0,
                                         0, 1, 0, 0,
                                         -sin(radians), 0, cos(radians), 0,
                                         0, 0, 0, 1);
  return rotation_y;
}

Matrix4 Matrix4::rotation_z(float radians) const {
  Matrix4 current = *this;
  Matrix4 rotation_z = current * Matrix4(cos(radians), -sin(radians), 0, 0,
                                         sin(radians), cos(radians), 0, 0,
                                         0, 0, 1, 0,
                                         0, 0, 0, 1);
  return rotation_z;
}

Matrix4 Matrix4::shearing(float x_y, float x_z, float y_x,
                          float y_z, float z_x, float z_y) const {
  Matrix4 current = *this;
  
  Matrix4 shearing = current * Matrix4(1, x_y, x_z, 0,
                                       y_x, 1, y_z, 0,
                                       z_x, z_y, 1, 0,
                                       0, 0, 0, 1);
  return shearing;
}

Matrix4 Matrix4::view_transform(const Point& from, const Point& to, const Vector& up) const {
  Vector forward = (to - from).normalize();
  Vector left = forward.cross(up.normalize());
  Vector true_up = left.cross(forward);
  Matrix4 orientation = Matrix4(left[0], left[1], left[2], 0,
                                true_up[0], true_up[1], true_up[2], 0,
                                -forward[0], -forward[1], -forward[2], 0,
                                0, 0, 0, 1);
  return orientation * Matrix4().translation(-from[0], -from[1], -from[2]);
}