#include "triangle.h"
#include "utils.h"
#include <algorithm>

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3)
  : Shape("triangle", ObjectType::kTriangle),
  p1_(p1), p2_(p2), p3_(p3), e1_(p2 - p1), e2_(p3 - p1), normal_(e2_.cross(e1_).normalize()) {}

bool Triangle::operator==(const Object& object) const {
  Triangle* other = (Triangle*)&object;
  return(name_ == other->GetName() &&
    transform_ == other->GetTransform() &&
    type_ == other->GetObjectType() &&
    parent_ == other->GetParent() &&
    id_ == other->GetID() &&
    material_ == other->GetMaterial() &&
    p1_ == other->GetP1() &&
    p2_ == other->GetP2() &&
    p3_ == other->GetP3());
}

Triangle& Triangle::operator=(const Object& object) {
  Triangle* other = (Triangle*)&object;
  name_ = other->GetName();
  type_ = other->GetObjectType();
  transform_ = other->GetTransform();
  material_ = other->GetMaterial();
  parent_ = other->GetParent();
  return *this;
}

std::vector<Intersection> Triangle::local_intersect(const utils::RayStruct& local_ray) {
  Vector dir_cross_e2 = local_ray.direction.cross(e2_);
  float determinant = e1_.dot(dir_cross_e2);

  if (abs(determinant) < utils::kEPSILON) {
    return {};
  }

  float f = 1.0f / determinant;

  Vector p1_to_origin = local_ray.origin - p1_;
  auto u = f * p1_to_origin.dot(dir_cross_e2);

  if (u < 0 || u > 1) return {};

  Vector origin_cross_e1 = p1_to_origin.cross(e1_);
  auto v = f * local_ray.direction.dot(origin_cross_e1);

  if (v < 0 || (u + v) > 1) return {};

  float t = f * e2_.dot(origin_cross_e1);
  return {Intersection(t, this)};
}

Vector Triangle::local_normal_at(const Point& local_point, const Intersection& hit) const {
  return normal_;
}

BoundingBox Triangle::bounds() const {
  return BoundingBox(Point(-1, -1, -1), Point(1, 1, 1));
}

Point Triangle::GetP1() const {
  return p1_;
}

Point Triangle::GetP2() const {
  return p2_;
}
Point Triangle::GetP3() const {
  return p3_;
}

Vector Triangle::GetE1() const {
  return e1_;
}

Vector Triangle::GetE2() const {
  return e2_;
}

Vector Triangle::GetNormal() const {
  return normal_;
}