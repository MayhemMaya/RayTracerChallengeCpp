
#include <iostream>
#include <cmath>
#include "vector.h"
#include "point.h"
#include "utils.h"

Vector::Vector(float x, float y, float z) : Tuple(x, y, z, 0) {}
Vector::Vector(const Tuple& t) : Tuple(t[0], t[1], t[2], t[3]) {}

std::ostream& operator<<(std::ostream& os, const Vector& obj) {
  os << "(" << obj[0] << ", " << obj[1] << ", " << obj[2] << ")";
  return os;
}

bool Vector::operator==(const Tuple& other) const {
  return(utils::equal((*this)[0], other[0]) && utils::equal((*this)[1], other[1]) &&
         utils::equal((*this)[2], other[2]) && utils::equal((*this)[3], other[3]));
}

Vector Vector::operator+(const Vector& other) const {
  return Vector((float)x_ + (float)other[0], (float)y_ + (float)other[1],
                                             (float)z_ + (float)other[2]);
}

Vector Vector::operator-(const Vector& other) const {
  return Vector((float)x_ - (float)other[0], (float)y_ - (float)other[1],
                                                 (float)z_ - (float)other[2]);
}

Vector Vector::operator-() const {
  return Vector(-x_, -y_, -z_);
}

Vector Vector::operator*(const float& scalar) const {
  return Vector((float)x_ * (float)scalar, (float)y_ * (float)scalar,
                                           (float)z_ * (float)scalar);
}

Vector Vector::operator/(const float& scalar) const {
  return Vector((float)x_ / (float)scalar, (float)y_ / (float)scalar,
                                           (float)z_ / (float)scalar);
}

double Vector::magnitude() const {
  return sqrt(pow((*this)[0], 2) + pow((*this)[1], 2) + pow((*this)[2], 2));
}

Vector Vector::normalize() const {
  return Vector(Tuple((*this)[0] / this->magnitude(),
                      (*this)[1] / this->magnitude(),
                      (*this)[2] / this->magnitude(),
                      (*this)[3] / this->magnitude()));
}