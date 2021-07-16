#pragma once

#include "matrix4.h"
#include "point.h"
#include "vector.h"

class TranslationMatrix : public Matrix4 {
 public:
  TranslationMatrix(float x, float y, float z);
  //Point operator*(const Point& other) const override;
  //Vector operator*(const Vector& other) const;
};
