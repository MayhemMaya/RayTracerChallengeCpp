#pragma once

#include "shape.h"

class Cone : public Shape {
public:
  Cone(const std::string& name, float minimum = -utils::kINFINITY, float maximum = utils::kINFINITY, bool closed = false);
  Cone(const std::string& name, const Material& material, float minimum = -utils::kINFINITY, float maximum = utils::kINFINITY, bool closed = false);
  Cone(const std::string& name, const Matrix4& transform, float minimum = -utils::kINFINITY, float maximum = utils::kINFINITY, bool closed = false);
  Cone(const std::string& name, const Material& material, const Matrix4& transform, float minimum = -utils::kINFINITY, float maximum = utils::kINFINITY, bool closed = false);
  bool operator==(const Object& object) override;
  Cone& operator=(const Object& object) override;
  std::vector<Intersection> local_intersect(const utils::RayStruct& local_ray) override;
  Vector local_normal_at(const Point& local_point) const override;
  float GetMinimum() const;
  float GetMaximum() const;
  bool GetClosed() const;
  void SetMinimum(float minimum);
  void SetMaximum(float maximum);
  void SetClosed(bool closed);

private:
  float minimum_, maximum_;
  bool closed_;
  void intersect_caps(const utils::RayStruct& local_ray, std::vector<Intersection>& xs);
};