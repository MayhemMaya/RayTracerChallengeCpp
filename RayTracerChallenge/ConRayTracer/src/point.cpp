
#include <iostream>
#include "point.h"
#include "utils.h"

Point::Point(float x, float y, float z) : Tuple(x, y, z, 1) {}

std::ostream& operator<<(std::ostream& os, const Point& obj) {
  os << "(" << obj.x_ << ", " << obj.y_ << ", " << obj.z_ << ")";
  return os;
}

bool Point::operator==(const Tuple& other) const {
  return(utils::equal(x_, other[0]) && utils::equal(y_, other[1]) &&
         utils::equal(z_, other[2]) && utils::equal(w_, other[3]));
}

Point Point::operator+(const Vector& other) const {
  return Point(x_ + other[0], y_ + other[1],
                              z_ + other[2]);
}

Vector Point::operator-(const Point& other) const {
  return Vector(x_ - other[0], y_ - other[1],
                               z_ - other[2]);
}

Point Point::operator-(const Vector& other) const {
  return Point(x_ - other[0], y_ - other[1],
                              z_ - other[2]);
}

Point Point::operator-() const {
  return Point(-x_, -y_, -z_);
}