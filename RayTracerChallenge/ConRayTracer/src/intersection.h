#pragma once

#include <vector>
#include "mesh.h"

class Intersection {
 public:
  Intersection();
  Intersection(float time, const Mesh& object);
  float GetTime() const;
  void SetTime(float time);
  Mesh GetObject() const;
  void SetObject(const Mesh& mesh);
  bool operator==(const Intersection& other) const;
  static void swap(Intersection& a, Intersection& b);
  static std::vector<Intersection> intersections(std::vector<Intersection> intersections);
 private:
  float time_;
  Mesh mesh_object_;
};
