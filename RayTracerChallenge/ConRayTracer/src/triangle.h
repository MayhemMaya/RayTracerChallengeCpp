#pragma once

#include "shape.h"
#include "point.h"
#include "vector.h"

class Triangle : public Shape {
 public:
  Triangle(const Point& p1, const Point& p2, const Point& p3);
  bool operator==(const Object& object) const override;
  Triangle& operator=(const Object& object) override;
  std::vector<Intersection> local_intersect(const utils::RayStruct& local_ray) override;
  Vector local_normal_at(const Point& local_point, const Intersection& hit = Intersection()) const override;
  BoundingBox bounds() const override final;
  Point GetP1() const;
  Point GetP2() const;
  Point GetP3() const;
  Vector GetE1() const;
  Vector GetE2() const;
  Vector GetNormal() const;
private:
  Point p1_, p2_, p3_;
  Vector e1_, e2_, normal_;
};