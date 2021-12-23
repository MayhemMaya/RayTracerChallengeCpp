
#include <iostream>
#include <cmath>
#include "vector.h"
#include "utils.h"

Vector::Vector(float x, float y, float z) : Tuple(x, y, z, 0) {}
Vector::Vector(const Tuple& tuple)
    : Tuple(tuple[0], tuple[1],
            tuple[2], tuple[3]) {}

std::ostream& operator<<(std::ostream& os, const Vector& obj) {
  os << "(" << obj.x_ << ", " << obj.y_ << ", " << obj.z_ << ")";
  return os;
}

bool Vector::operator==(const Tuple& other) const {
  return(utils::equal(x_, other[0]) && utils::equal(y_, other[1]) &&
         utils::equal(z_, other[2]) && utils::equal(w_, other[3]));
}

Vector Vector::operator+(const Vector& other) const {
  return Vector(x_ + other[0], y_ + other[1],
                               z_ + other[2]);
}

Vector Vector::operator-(const Vector& other) const {
  return Vector(x_ - other[0], y_ - other[1],
                               z_ - other[2]);
}

Vector Vector::operator-() const {
  return Vector(-x_, -y_, -z_);
}

Vector Vector::operator*(const float& scalar) const {
  return Vector(x_ * scalar, y_ * scalar,
                             z_ * scalar);
}

Vector Vector::operator/(const float& scalar) const {
  return Vector(x_ / scalar, y_ / scalar,
                             z_ / scalar);
}

float Vector::magnitude() const {
  return (float)sqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2));
}

Vector Vector::normalize() const {
  return Vector(Tuple(x_ / this->magnitude(),
                      y_ / this->magnitude(),
                      z_ / this->magnitude(),
                      w_ / this->magnitude()));
}

Vector Vector::reflect(const Vector& normal) const {
  return (*this - normal * 2 * utils::dot(*this, normal));
}