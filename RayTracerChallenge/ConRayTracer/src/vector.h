#pragma once

#include "tuple.h"

class Vector : public Tuple {
 public:
  Vector();
  Vector(float x, float y, float z);
  friend std::ostream& operator<<(std::ostream& os, const Vector& obj);
  bool operator == (const Tuple& other) const;
  Vector operator + (const Vector& other) const;
  Vector operator - (const Vector& other) const;
  Vector operator - () const;
  Vector operator * (const float& other) const;
  Vector operator / (const float& other) const;
  float magnitude() const;
  Vector normalize() const;
  Vector reflect(const Vector& normal) const;
  float dot(const Vector& other) const;
  Vector cross(const Vector& other) const;
};
