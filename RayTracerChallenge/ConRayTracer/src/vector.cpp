
#include <cmath>
#include "vector.h"
#include "utils.h"

Vector::Vector() : Tuple(0.0f, 0.0f, 0.0f, 0.0f) {}
Vector::Vector(float x, float y, float z) : Tuple(x, y, z, 0.0f) {}

std::ostream& operator<<(std::ostream& os, const Vector& obj) {
  os << "(" << obj.x_ << ", " << obj.y_ << ", " << obj.z_ << ")" << "\n";
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
  /*
  return Vector(Tuple(x_ / this->magnitude(),
                      y_ / this->magnitude(),
                      z_ / this->magnitude(),
                      w_ / this->magnitude()));*/
  return Vector(x_ / this->magnitude(),
    y_ / this->magnitude(),
    z_ / this->magnitude());
}

Vector Vector::reflect(const Vector& normal) const {
  return (*this - normal * 2 * this->dot(normal));
}

float Vector::dot(const Vector& other) const {
  return((*this)[0] * other[0] +
         (*this)[1] * other[1] +
         (*this)[2] * other[2] +
         (*this)[3] * other[3]);
}

Vector Vector::cross(const Vector& other) const {
  return Vector((*this)[1] * other[2] - (*this)[2] * other[1],
                (*this)[2] * other[0] - (*this)[0] * other[2],
                (*this)[0] * other[1] - (*this)[1] * other[0]);
}