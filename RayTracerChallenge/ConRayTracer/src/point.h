#pragma once

#include "tuple.h"
#include "vector.h"

class Point : public Tuple {
 public:
  Point();
  Point(float x, float y, float z);
  friend std::ostream& operator<<(std::ostream& os, const Point& obj);
  bool operator == (const Tuple& other) const;
  Point operator + (const Vector& other) const;
  Vector operator - (const Point&) const;
  Point operator - (const Vector&) const;
  Point operator - () const;
};
