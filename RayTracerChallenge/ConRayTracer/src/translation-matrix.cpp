#include "translation-matrix.h"
#include "point.h"
#include "vector.h"

TranslationMatrix::TranslationMatrix(float x, float y, float z)
    : Matrix4(1, 0, 0, x,
              0, 1, 0, y,
              0, 0, 1, z,
              0, 0, 0, 1) {}

/*
Point TranslationMatrix::operator*(const Point& other) const {
  Point p(0, 0, 0);

  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      float temp = (*this)(r, 0) * other[0] +
                   (*this)(r, 1) * other[1] +
                   (*this)(r, 2) * other[2] +
                   (*this)(r, 3) * other[3];
      p(r, temp);
    }
  }
  return p;
}

Vector TranslationMatrix::operator*(const Vector& other) const {
  Vector v(0, 0, 0);

  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      float temp = (*this)(r, 0) * other[0] +
                   (*this)(r, 1) * other[1] +
                   (*this)(r, 2) * other[2] +
                   (*this)(r, 3) * other[3];
      v(r, temp);
    }
  }
  return v;
}*/