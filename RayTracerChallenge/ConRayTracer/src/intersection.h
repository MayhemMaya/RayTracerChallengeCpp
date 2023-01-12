#pragma once

#include <vector>
#include "object.h"

class Intersection {
 public:
  Intersection();
  Intersection(float time, Object* object);
  Intersection(const Intersection& other);
  ~Intersection();
  float GetTime() const;
  void SetTime(float time);
  Object* GetObject() const;
  void SetObject(Object* object);
  bool operator==(const Intersection& other) const;
  Intersection& operator=(const Intersection& other);
  static void swap(Intersection& a, Intersection& b);
  static std::vector<Intersection> intersections(const std::vector<Intersection>& intersections);
 private:
  float time_;
  Object* object_;
};
