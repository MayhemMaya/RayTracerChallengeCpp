#include <cmath>
#include <vector>
#include "ray.h"
#include "sphere.h"
#include "point.h"
#include "vector.h"
#include "utils.h"
#include "intersection.h"
#include "translation-matrix.h"
#include "scaling-matrix.h"

Ray::Ray(Point origin, Vector direction)
    : origin_(origin), direction_(direction) {}

Point Ray::GetOrigin() const {
  return origin_;
}

Vector Ray::GetDirection() const {
  return direction_;
}

Point Ray::position(float time) const {
  return(origin_ + direction_ * time);
}

std::vector<Intersection> Ray::intersect(const Sphere& sphere) const {
  Ray ray2 = this->transform(sphere.GetTransform().inverse());
  Vector sphere_to_ray = ray2.GetOrigin() - sphere.GetPosition();

  float a = utils::dot(ray2.GetDirection(), ray2.GetDirection());
  float b = 2 * utils::dot(ray2.GetDirection(), sphere_to_ray);
  float c = utils::dot(sphere_to_ray, sphere_to_ray) - 1;
  float discriminant = pow(b, 2) - 4 * a * c;
  if (discriminant < 0) return {};
  float t1 = (-b - sqrt(discriminant)) / (2 * a);
  float t2 = (-b + sqrt(discriminant)) / (2 * a);
  Intersection i1(t1, sphere);
  Intersection i2(t2, sphere);
  return { i1, i2 };
}

Ray Ray::transform(const Matrix4& matrix) const {
  Point new_origin = matrix * origin_;
  Vector new_direction = matrix * direction_;
  return Ray(new_origin, new_direction);
}