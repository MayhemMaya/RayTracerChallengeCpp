#pragma once

#include <iostream>
#include "utils.h"
#include <array>

class Matrix2 {
 public:
  Matrix2();
  Matrix2(float a11, float a12,
          float a21, float a22);
  float operator()(int y, int x) const;
  void operator()(int y, int x, float value);
  friend std::ostream& operator<<(std::ostream& os, const Matrix2& obj);
  bool operator==(const Matrix2& other) const;
  bool operator!=(const Matrix2& other) const;
  float determinant() const;
 private:
   std::array<std::array<float, 2>, 2> data_;
};
