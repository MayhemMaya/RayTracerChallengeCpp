#pragma once

#include "shape.h"

class Plane : public Shape {
 public:
  Plane();
  Plane(const std::string& name);
  Plane(const Material& material);
  Plane(const Matrix4& transform);
  Plane(const std::string& name, const Material& material);
  Plane(const std::string& name, const Matrix4& transform);
  Plane(const Material& material, const Matrix4& transform);
  Plane(const std::string& name, const Material& material, const Matrix4& transform);
  bool operator==(const Object& object) override;
  Plane& operator=(const Object& other) override;
  std::vector<Intersection> local_intersect(const utils::RayStruct& local_ray) override;
  Vector local_normal_at(const Point& local_point) const override;
};
