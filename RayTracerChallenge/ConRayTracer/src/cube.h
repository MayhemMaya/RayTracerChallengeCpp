#pragma once

#include "shape.h"

struct TimeValuePair {
  float tmin, tmax;
};

class Cube : public Shape {
public:
  Cube();
  Cube(const std::string& name);
  Cube(const Material& material);
  Cube(const Matrix4& transform);
  Cube(const std::string& name, const Material& material);
  Cube(const std::string& name, const Matrix4& transform);
  Cube(const Material& material, const Matrix4& transform);
  Cube(const std::string& name, const Material& material, const Matrix4& transform);
  bool operator==(const Object& object) override;
  Cube& operator=(const Object& object) override;
  std::vector<Intersection> local_intersect(const utils::RayStruct& local_ray) override;
  Vector local_normal_at(const Point& local_point) const override;
};