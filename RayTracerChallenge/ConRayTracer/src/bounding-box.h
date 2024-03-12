#pragma once

#include "intersection.h"
#include "point.h"
#include "materials.h"

class BoundingBox {
public:
  BoundingBox();
  BoundingBox(const Point& minimum, const Point& maximum);
  Point GetMinimum() const;
  Point GetMaximum() const;
  void SetMinimum(const Point& minimum);
  void SetMaximum(const Point& maximum);
  void merge(const BoundingBox& other);
  void extend_to_fit(const Point& point);
  BoundingBox transform(const Matrix4& transform);
  bool equal(const BoundingBox& other, bool precise) const;
private:
  Point minimum_;
  Point maximum_;
};