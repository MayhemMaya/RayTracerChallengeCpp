#include <iostream>
#include "tuple.h"

Tuple::Tuple() : x_(0), y_(0), z_(0), w_(0) {}
Tuple::Tuple(float x, float y, float z, float w)
    : x_(x), y_(y), z_(z), w_(w) {}

Tuple::~Tuple() {}

float Tuple::operator[] (int index) const {
  switch (index) {
  case 0: return x_;
  case 1: return y_;
  case 2: return z_;
  case 3: return w_;
  }
}

void Tuple::operator()(int index, float value) {
  switch (index) {
  case 0:
    x_ = value;
    break;
  case 1:
    y_ = value;
    break;
  case 2:
    z_ = value;
    break;
  case 3:
    w_ = value;
    break;
  }
}

bool Tuple::IsPoint() const { return w_ == 1.0F; }
bool Tuple::IsVector() const { return w_ == 0.0F; }
