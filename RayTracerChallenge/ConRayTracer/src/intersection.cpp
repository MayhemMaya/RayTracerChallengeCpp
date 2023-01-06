#include <vector>
#include "intersection.h"
#include "shape.h"

Intersection::Intersection()
    : time_(0.0), shape_object_(nullptr) {}

Intersection::Intersection(float time, Shape* object)
    : time_(time), shape_object_(object) {}

Intersection::Intersection(const Intersection& other)
  : time_(other.GetTime()), shape_object_(other.GetObject()) {}

Intersection::~Intersection() {
  shape_object_ = nullptr;
  delete shape_object_;
}

float Intersection::GetTime() const {
  return time_;
}

void Intersection::SetTime(float time) {
  time_ = time;
}
Shape* Intersection::GetObject() const {
  return shape_object_;
}

void Intersection::SetObject(Shape* object) {
  shape_object_ = object;
}

bool Intersection::operator==(const Intersection& other) const {
  return(time_ == other.GetTime() && shape_object_ == other.GetObject());
}

Intersection& Intersection::operator=(const Intersection& other) {
  this->SetTime(other.GetTime());
  this->SetObject(other.GetObject());
  return *this;
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

std::vector<Intersection> Intersection::intersections(const std::vector<Intersection>& intersections) {
  if (intersections.size() <= 0) return intersections;
  std::vector<Intersection> xs = intersections;
  for (int i = 0; i < xs.size() - 1; i++) {
    for (int j = 0; j < xs.size()-i-1; j++)
      if (xs[j].GetTime() > xs[j + 1].GetTime())
        swap(xs[j], xs[j + 1]);
  }
  return xs;
}