#pragma once

#include <iostream>
#include "tuple.h"

class Vector : public Tuple {
 public:
  Vector(float x, float y, float z);
  Vector(const Tuple& tuple);
  friend std::ostream& operator<<(std::ostream& os, const Vector& obj);
  bool operator == (const Tuple& other) const;
  Vector operator + (const Vector& other) const;
  Vector operator - (const Vector& other) const;
  Vector operator - () const;
  Vector operator * (const float& other) const;
  Vector operator / (const float& other) const;
  double magnitude() const;
  Vector normalize() const;
};
