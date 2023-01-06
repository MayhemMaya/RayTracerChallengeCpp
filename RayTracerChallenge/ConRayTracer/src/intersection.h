#pragma once

#include <vector>
#include "shape.h"

class Intersection {
 public:
  Intersection();
  Intersection(float time, Shape* object);
  Intersection(const Intersection& other);
  ~Intersection();
  float GetTime() const;
  void SetTime(float time);
  Shape* GetObject() const;
  void SetObject(Shape* object);
  bool operator==(const Intersection& other) const;
  Intersection& operator=(const Intersection& other);
  static void swap(Intersection& a, Intersection& b);
  static std::vector<Intersection> intersections(const std::vector<Intersection>& intersections);
 private:
  float time_;
  Shape* shape_object_;
};
