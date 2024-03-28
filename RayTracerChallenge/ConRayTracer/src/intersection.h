#pragma once

#include <vector>
#include "object.h"

class Intersection {
 public:
  Intersection() = default;
  Intersection(float time, Object* object);
  Intersection(float time, Object* object, float u, float v);
  Intersection(const Intersection& other);
  ~Intersection();
  float GetTime() const;
  void SetTime(float time);
  Object* GetObject() const;
  void SetObject(Object* object);
  float GetU() const;
  void SetU(float u);
  float GetV() const;
  void SetV(float v);
  bool operator==(const Intersection& other) const;
  Intersection& operator=(const Intersection& other);
  static void swap(Intersection& a, Intersection& b);
  static std::vector<Intersection> intersections(const std::vector<Intersection>& intersections);
 private:
  float time_ = 0.0f;
  Object* object_ = nullptr;
  float u_ = -1.0f;
  float v_ = -1.0f;
};
