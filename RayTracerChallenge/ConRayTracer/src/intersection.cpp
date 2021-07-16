#include <vector>
#include "intersection.h"
#include "object.h"

Intersection::Intersection()
    : time_(0.0), object_() {}

Intersection::Intersection(float time, const Object& object)
    : time_(time), object_(object) {}

float Intersection::GetTime() const {
  return time_;
}
Object Intersection::GetObject() const {
  return object_;
}

bool Intersection::operator==(const Intersection& other) const {
  return(time_ == other.GetTime() && object_ == other.GetObject());
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