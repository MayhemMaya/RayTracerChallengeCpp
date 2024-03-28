#include <vector>
#include "intersection.h"
#include "object.h"

Intersection::Intersection(float time, Object* object)
  : time_(time), u_(-1.0f), v_(-1.0f), object_(object) {}

Intersection::Intersection(float time, Object* object, float u, float v)
  : time_(time), object_(object), u_(u), v_(v) {}

Intersection::Intersection(const Intersection& other)
  : time_(other.GetTime()), u_(other.GetU()), v_(other.GetV()), object_(other.GetObject()) {}

Intersection::~Intersection() {
  object_ = nullptr;
  delete object_;
}

float Intersection::GetTime() const {
  return time_;
}

void Intersection::SetTime(float time) {
  time_ = time;
}
Object* Intersection::GetObject() const {
  return object_;
}

void Intersection::SetObject(Object* object) {
  object_ = object;
}

float Intersection::GetU() const {
  return u_;
}

void Intersection::SetU(float u) {
  u_ = u;
}

float Intersection::GetV() const {
  return v_;
}

void Intersection::SetV(float v) {
  v_ = v;
}

bool Intersection::operator==(const Intersection& other) const {
  return(time_ == other.GetTime() &&
         *object_ == *other.GetObject() &&
         this->GetU() == other.GetU() &&
         this->GetV() == other.GetV());
}

Intersection& Intersection::operator=(const Intersection& other) {
  this->SetTime(other.GetTime());
  this->SetObject(other.GetObject());
  this->SetU(other.GetU());
  this->SetV(other.GetV());
  return *this;
}

void Intersection::swap(Intersection& a, Intersection& b) {
  Intersection temp;

  temp.SetTime(a.GetTime());
  temp.SetObject(a.GetObject());
  temp.SetU(a.GetU());
  temp.SetV(a.GetV());

  a.SetTime(b.GetTime());
  a.SetObject(b.GetObject());
  a.SetU(b.GetU());
  a.SetV(b.GetV());

  b.SetTime(temp.GetTime());
  b.SetObject(temp.GetObject());
  b.SetU(temp.GetU());
  b.SetV(temp.GetV());
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