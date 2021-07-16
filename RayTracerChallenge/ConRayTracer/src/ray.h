#pragma once

#include <vector>
#include "sphere.h"
#include "point.h"
#include "vector.h"
#include "intersection.h"
#include "matrix4.h"

class Ray {
 public:
  Ray(Point origin, Vector direction);
  Point GetOrigin() const;
  Vector GetDirection() const;
  Point position(float time) const;
  std::vector<Intersection> intersect(const Sphere& obj) const;
  Ray transform(const Matrix4& matrix) const;
 private:
  Point origin_;
  Vector direction_;
};
