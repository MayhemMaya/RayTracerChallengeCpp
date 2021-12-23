#include <cmath>
#include <vector>
#include "ray.h"
#include "sphere.h"
#include "point.h"
#include "vector.h"
#include "utils.h"
#include "intersection.h"

Ray::Ray(const Point& origin, const Vector& direction)
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

std::vector<float> Ray::intersect(const Sphere& sphere) const {
  Matrix4 sphere_inverse = sphere.GetTransform().inverse();
  Ray ray2 = this->transform(sphere_inverse);
  
  Vector sphere_to_ray = ray2.GetOrigin() - Point(0, 0, 0);

  float a = utils::dot(ray2.GetDirection(), ray2.GetDirection());
  float b = 2.0f * utils::dot(ray2.GetDirection(), sphere_to_ray);
  float c = utils::dot(sphere_to_ray, sphere_to_ray) - 1;
  float discriminant = pow(b, 2) - 4 * a * c;
  if (discriminant < 0) return {};
  float t1 = (-b - sqrt(discriminant)) / (2 * a);
  float t2 = (-b + sqrt(discriminant)) / (2 * a);
  
  return { t1, t2 };
}

std::vector<Intersection> Ray::intersect(const World& world) const {
  std::vector<Intersection> intersections;
  
  for (Mesh* m : world.GetMeshes()) {
    Sphere* s = (Sphere*)m;
    for (float t : this->intersect((*s))) {
      Intersection i(t, s);
      intersections.push_back(i);
    }
  }
  return Intersection::intersections(intersections);
}

Ray Ray::transform(const Matrix4& matrix) const {
  Point new_origin = matrix * origin_;
  Vector new_direction = matrix * direction_;
  return Ray(new_origin, new_direction);
}