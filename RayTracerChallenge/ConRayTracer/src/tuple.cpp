#include <iostream>
#include "tuple.h"

Tuple::Tuple(float x, float y, float z, float w)
    : x_(x), y_(y), z_(z), w_(w) {}

Tuple::~Tuple() {}

std::ostream& operator<<(std::ostream& os, const Tuple& obj) {
  os << "(" << obj.x_ << ", " << obj.y_ << ", " << obj.z_ << ", " << obj.w_ << ")";
  return os;
}

float Tuple::operator[] (unsigned int index) const {
  switch (index) {
  case 0: return x_;
  case 1: return y_;
  case 2: return z_;
  case 3: return w_;
  }
}

bool Tuple::operator==(const Tuple& other) const {
  return(x_ == other[0] && y_ == other[1] &&
         z_ == other[2] && w_ == other[3]);
}

bool Tuple::IsPoint() const { return(w_ == 1.0F); }
bool Tuple::IsVector() const { return(w_ == 0.0F); }

Tuple Tuple::operator+(const Tuple& other) const {
  if ((w_ + other[3]) < 2) {
    return Tuple(x_ + other[0], y_ + other[1], z_ +
                      other[2], w_ + other[3]);
  }
  else {
    std::cout << "Cannot add two Points!" << std::endl;
  }
}

Tuple Tuple::operator-(const Tuple& other) const {
  return Tuple((float)x_ - (float)other[0], (float)y_ - (float)other[1],
               (float)z_ - (float)other[2], (float)w_ - (float)other[3]);
}

Tuple Tuple::operator-() const {
  return Tuple(-x_, -y_, -z_, -w_);
}

Tuple Tuple::operator*(const float& scalar) const {
  return Tuple((float)x_ * (float)scalar, (float)y_ * (float)scalar,
               (float)z_ * (float)scalar, (float)w_ * (float)scalar);
}

Tuple Tuple::operator/(const float& scalar) const {
  return Tuple((float)x_ / (float)scalar, (float)y_ / (float)scalar,
               (float)z_ / (float)scalar, (float)w_ / (float)scalar);
}
