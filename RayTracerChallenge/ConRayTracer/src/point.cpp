
#include "point.h"
#include "utils.h"

Point::Point(float x, float y, float z) : Tuple(x, y, z, 1) {}

std::ostream& operator<<(std::ostream& os, const Point& obj) {
  os << "(" << obj[0] << ", " << obj[1] << ", " << obj[2] << ")";
  return os;
}

bool Point::operator==(const Tuple& other) const {
  return(utils::equal((*this)[0], other[0]) && utils::equal((*this)[1], other[1]) &&
         utils::equal((*this)[2], other[2]) && utils::equal((*this)[3], other[3]));
}

Point Point::operator+(const Vector& other) const {
  return Point((float)x_ + (float)other[0], (float)y_ + (float)other[1],
                                            (float)z_ + (float)other[2]);
}

Vector Point::operator-(const Point& other) const {
  return Vector((float)x_ - (float)other[0], (float)y_ - (float)other[1],
                                             (float)z_ - (float)other[2]);
}

Point Point::operator-(const Vector& other) const {
  return Point((float)x_ - (float)other[0], (float)y_ - (float)other[1],
                                            (float)z_ - (float)other[2]);
}

Point Point::operator-() const {
  return Point(-x_, -y_, -z_);
}