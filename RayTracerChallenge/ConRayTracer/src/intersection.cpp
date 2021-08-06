#include <vector>
#include "intersection.h"
#include "mesh.h"

Intersection::Intersection()
    : time_(0.0), mesh_object_("") {}

Intersection::Intersection(float time, const Mesh& object)
    : time_(time), mesh_object_(object) {}

float Intersection::GetTime() const {
  return time_;
}
Mesh Intersection::GetObject() const {
  return mesh_object_;
}

bool Intersection::operator==(const Intersection& other) const {
  return(time_ == other.GetTime() && mesh_object_ == other.GetObject());
}

void swap(Intersection& a, Intersection& b) {
  Intersection temp = a;
  a = b;
  b = temp;
}

std::vector<Intersection> Intersection::intersections(std::vector<Intersection> intersections) {
  std::vector<Intersection> objs = intersections;
  for (int i = 0; i < objs.size() - 1; i++) {
    for (int j = 0; j < objs.size() - 1; j++) {
      if (objs[j].GetTime() > objs[j + 1].GetTime()) {
        swap(objs[j], objs[j + 1]);
      }
    }
  }
  return objs;
}