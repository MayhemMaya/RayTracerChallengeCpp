#pragma once

#include "shape.h"

class Cube : public Shape {
public:
  Cube();
  Cube(const std::string& name);
  Cube(const std::string& name, const Material& material);
  Cube(const std::string& name, const Matrix4& transform);
  Cube(const std::string& name, const Material& material, const Matrix4& transform);
  bool operator==(const Object& object) const override;
  Cube& operator=(const Object& object) override;
  std::vector<Intersection> local_intersect(const utils::RayStruct& local_ray) override;
  Vector local_normal_at(const Point& local_point, const Intersection& hit = Intersection()) const override;
  BoundingBox bounds() const override final;
};