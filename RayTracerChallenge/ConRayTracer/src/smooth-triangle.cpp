#include "smooth-triangle.h"
#include "utils.h"
#include <algorithm>

SmoothTriangle::SmoothTriangle(const Point& p1, const Point& p2, const Point& p3, const Vector& n1, const Vector& n2, const Vector& n3)
  : Shape("triangle", ObjectType::kTriangle),
  p1_(p1), p2_(p2), p3_(p3), e1_(p2 - p1), e2_(p3 - p1), n1_(n1), n2_(n2), n3_(n3) {}

bool SmoothTriangle::operator==(const Object& object) const {
  SmoothTriangle* other = (SmoothTriangle*)&object;
  return(name_ == other->GetName() &&
    transform_ == other->GetTransform() &&
    type_ == other->GetObjectType() &&
    parent_ == other->GetParent() &&
    //id_ == other->GetID() &&
    material_ == other->GetMaterial() &&
    p1_ == other->GetP1() &&
    p2_ == other->GetP2() &&
    p3_ == other->GetP3() &&
    n1_ == other->GetN1() &&
    n2_ == other->GetN2() &&
    n3_ == other->GetN3());
}

SmoothTriangle& SmoothTriangle::operator=(const Object& object) {
  SmoothTriangle* other = (SmoothTriangle*)&object;
  name_ = other->GetName();
  type_ = other->GetObjectType();
  transform_ = other->GetTransform();
  material_ = other->GetMaterial();
  parent_ = other->GetParent();
  return *this;
}

std::vector<Intersection> SmoothTriangle::local_intersect(const utils::RayStruct& local_ray) {
  Vector dir_cross_e2 = local_ray.direction.cross(e2_);
  float determinant = e1_.dot(dir_cross_e2);

  if (abs(determinant) < utils::kEPSILON) {
    return {};
  }

  float f = 1.0f / determinant;

  Vector p1_to_origin = local_ray.origin - p1_;
  float u = f * p1_to_origin.dot(dir_cross_e2);

  if (u < 0 || u > 1) return {};

  Vector origin_cross_e1 = p1_to_origin.cross(e1_);
  float v = f * local_ray.direction.dot(origin_cross_e1);

  if (v < 0 || (u + v) > 1) return {};

  float t = f * e2_.dot(origin_cross_e1);
  return { Intersection(t, this, u, v) };
}

Vector SmoothTriangle::local_normal_at(const Point& local_point, const Intersection& hit) const {
  return (
    this->n2_ * hit.GetU() +
    this->n3_ * hit.GetV() +
    this->n1_ * (1 - hit.GetU() - hit.GetV())
 );
}

BoundingBox SmoothTriangle::bounds() const {
  return BoundingBox(Point(-1, -1, -1), Point(1, 1, 1));
}

Point SmoothTriangle::GetP1() const {
  return p1_;
}

Point SmoothTriangle::GetP2() const {
  return p2_;
}
Point SmoothTriangle::GetP3() const {
  return p3_;
}

Vector SmoothTriangle::GetN1() const {
  return n1_;
}

Vector SmoothTriangle::GetN2() const {
  return n2_;
}

Vector SmoothTriangle::GetN3() const {
  return n3_;
}