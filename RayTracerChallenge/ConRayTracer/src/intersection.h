#pragma once

#include <vector>
#include "object.h"

class Intersection {
 public:
  Intersection();
  Intersection(float time, const Object& object);
  float GetTime() const;
  Object GetObject() const;
  bool operator==(const Intersection& other) const;
  static std::vector<Intersection> intersections(std::vector<Intersection> intersections);
 private:
  float time_;
  Object object_;
};
