#pragma once

#include "object.h"
#include "material.h"
#include "vector.h"
#include "point.h"

class Mesh : public Object {
 public:
  Mesh(std::string name);
  virtual ~Mesh();
  Vector normal_at(const Point& world_point) const;
  Material GetMaterial() const;
  void SetMaterial(const Material& material);
  static int GetCount();
 private:
  static int mesh_count_;
  Material material_;
};
