#include <vector>
#include "intersection.h"
#include "mesh.h"

Intersection::Intersection()
    : time_(0.0), mesh_object_(Mesh("", ObjectType::kUnknown)) {}

Intersection::Intersection(float time, const Mesh& object)
    : time_(time), mesh_object_(object) {}

float Intersection::GetTime() const {
  return time_;
}

void Intersection::SetTime(float time) {
  time_ = time;
}
Mesh Intersection::GetObject() const {
  return mesh_object_;
}

void Intersection::SetObject(const Mesh& mesh) {
  mesh_object_ = mesh;
}

bool Intersection::operator==(const Intersection& other) const {
  return(time_ == other.GetTime() && mesh_object_ == other.GetObject());
}

void Intersection::swap(Intersection& a, Intersection& b) {
  Intersection temp;
  temp.SetTime(a.GetTime());
  temp.SetObject(a.GetObject());

  a.SetTime(b.GetTime());
  a.SetObject(b.GetObject());

  b.SetTime(temp.GetTime());
  b.SetObject(temp.GetObject());
}

std::vector<Intersection> Intersection::intersections(std::vector<Intersection> intersections) {
  if (intersections.size() <= 0) return intersections;
  std::vector<Intersection> xs = intersections;
  for (int i = 0; i < xs.size() - 1; i++) {
    for (int j = 0; j < xs.size()-i-1; j++)
      if (xs[j].GetTime() > xs[j + 1].GetTime())
        swap(xs[j], xs[j + 1]);
  }
    
  return xs;
}