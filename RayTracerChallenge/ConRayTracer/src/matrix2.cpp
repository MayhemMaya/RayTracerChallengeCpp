#include <iostream>
#include "Matrix2.h"
#include "utils.h"

Matrix2::Matrix2() {}

Matrix2::Matrix2(float a11, float a12, 
                 float a21, float a22) {
  data_[0][0] = a11;
  data_[0][1] = a12;
  data_[1][0] = a21;
  data_[1][1] = a22;
}

float Matrix2::operator()(unsigned int y, unsigned int x) const {
  return data_[y][x];
}

void Matrix2::operator()(unsigned int y, unsigned int x, float value) {
  data_[y][x] = value;
}

std::ostream& operator<<(std::ostream& os, const Matrix2& obj) {
  for (int r = 0; r < 2; r++) {
    os << "[";
    for (int c = 0; c < 2; c++) {
      if (c < 1)
        os << obj(r, c) << ", ";
      else os << obj(r, c);
    }
    os << "]" << std::endl;
  }
  return os;
}

bool Matrix2::operator==(const Matrix2& other) const {
  return(utils::equal(data_[0][0], other(0, 0)) &&
         utils::equal(data_[0][1], other(0, 1)) &&
         utils::equal(data_[1][0], other(1, 0)) &&
         utils::equal(data_[1][1], other(1, 1)));
}

bool Matrix2::operator!=(const Matrix2& other) const {
  return(!utils::equal(data_[0][0], other(0, 0)) &&
         !utils::equal(data_[0][1], other(0, 1)) &&
         !utils::equal(data_[1][0], other(1, 0)) &&
         !utils::equal(data_[1][1], other(1, 1)));
}

float Matrix2::determinant() const {
  return(data_[0][0] * data_[1][1] - data_[0][1] * data_[1][0]);
}