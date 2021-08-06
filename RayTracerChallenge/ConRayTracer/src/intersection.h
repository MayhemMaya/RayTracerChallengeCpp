#pragma once

#include <vector>
#include "mesh.h"

class Intersection {
 public:
  Intersection();
  Intersection(float time, const Mesh& object);
  float GetTime() const;
  Mesh GetObject() const;
  bool operator==(const Intersection& other) const;
  static std::vector<Intersection> intersections(std::vector<Intersection> intersections);
 private:
  float time_;
  Mesh mesh_object_;
};
