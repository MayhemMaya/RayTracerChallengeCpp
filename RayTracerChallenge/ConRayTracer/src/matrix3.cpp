#include <iostream>
#include <vector>
#include "Matrix3.h"
#include "Matrix2.h"
#include "utils.h"

Matrix3::Matrix3() {}

Matrix3::Matrix3(float a11, float a12, float a13,
                 float a21, float a22, float a23,
                 float a31, float a32, float a33) {
  data_[0][0] = a11;
  data_[0][1] = a12;
  data_[0][2] = a13;
  data_[1][0] = a21;
  data_[1][1] = a22;
  data_[1][2] = a23;
  data_[2][0] = a31;
  data_[2][1] = a32;
  data_[2][2] = a33;
}

float Matrix3::operator()(unsigned int y, unsigned int x) const {
  return data_[y][x];
}

void Matrix3::operator()(unsigned int y, unsigned int x, float value) {
  data_[y][x] = value;
}

std::ostream& operator<<(std::ostream& os, const Matrix3& obj) {
  for (int r = 0; r < 3; r++) {
    os << "[";
    for (int c = 0; c < 3; c++) {
      if (c < 2)
        os << obj(r, c) << ", ";
      else os << obj(r, c);
    }
    os << "]" << std::endl;
  }
  return os;
}

bool Matrix3::operator==(const Matrix3& other) const {
  return(utils::equal(data_[0][0], other(0, 0)) &&
         utils::equal(data_[0][1], other(0, 1)) &&
         utils::equal(data_[0][2], other(0, 2)) &&
         utils::equal(data_[1][0], other(1, 0)) &&
         utils::equal(data_[1][1], other(1, 1)) &&
         utils::equal(data_[1][2], other(1, 2)) &&
         utils::equal(data_[2][0], other(2, 0)) &&
         utils::equal(data_[2][1], other(2, 1)) &&
         utils::equal(data_[2][2], other(2, 2)));
}

bool Matrix3::operator!=(const Matrix3& other) const {
  return(!utils::equal(data_[0][0], other(0, 0)) &&
         !utils::equal(data_[0][1], other(0, 1)) &&
         !utils::equal(data_[0][2], other(0, 2)) &&
         !utils::equal(data_[1][0], other(1, 0)) &&
         !utils::equal(data_[1][1], other(1, 1)) &&
         !utils::equal(data_[1][2], other(1, 2)) &&
         !utils::equal(data_[2][0], other(2, 0)) &&
         !utils::equal(data_[2][1], other(2, 1)) &&
         !utils::equal(data_[2][2], other(2, 2)));
}

Matrix2 Matrix3::submatrix(int row, int col) const {
  std::vector<float> temps;
  for (int r = 0; r < 3; r++) {
    if (r == row) continue;
    for (int c = 0; c < 3; c++) {
      if (c == col) continue;
      temps.push_back(data_[r][c]);
    }
  }

  Matrix2 M;
  for (int r = 0; r < 2; r++) {
    for (int c = 0; c < 2; c++) {
      int i = 2 * r + c;
      M(r, c, temps[i]);
    }
  }
  return M;
}

float Matrix3::minor(int row, int col) const {
  Matrix2 M = this->submatrix(row, col);
  return M.determinant();
}

float Matrix3::cofactor(int row, int col) const {
  float minor = this->minor(row, col);
  if ((row + col) % 2 == 1)
    return -minor;
  return minor;
}

float Matrix3::determinant() const {
  float det = data_[0][0] * cofactor(0, 0) +
              data_[0][1] * cofactor(0, 1) +
              data_[0][2] * cofactor(0, 2);
  return det;
}