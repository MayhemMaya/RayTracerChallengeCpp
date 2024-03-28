#pragma once

#include "shape.h"
#include "point.h"
#include "vector.h"

class SmoothTriangle : public Shape {
public:
  SmoothTriangle(const Point& p1, const Point& p2, const Point& p3, const Vector& n1, const Vector& n2, const Vector& n3);
  bool operator==(const Object& object) const override;
  SmoothTriangle& operator=(const Object& object) override;
  std::vector<Intersection> local_intersect(const utils::RayStruct& local_ray) override;
  Vector local_normal_at(const Point& local_point, const Intersection& hit = Intersection()) const override;
  BoundingBox bounds() const override final;
  Point GetP1() const;
  Point GetP2() const;
  Point GetP3() const;
  Vector GetN1() const;
  Vector GetN2() const;
  Vector GetN3() const;
private:
  Point p1_, p2_, p3_;
  Vector e1_, e2_, n1_, n2_, n3_;
};