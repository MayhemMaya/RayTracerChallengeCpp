#include <iostream>
#include "mock-tuple.h"

MockTuple::MockTuple() : Tuple() {}

MockTuple::MockTuple(float x, float y, float z, float w) : Tuple(x, y, z, w) {}

MockTuple MockTuple::operator+(const MockTuple& other) const {
  if ((w_ + other[3]) < 2) {
    return MockTuple(x_ + other[0], y_ + other[1], z_ +
      other[2], w_ + other[3]);
  }
  else {
    std::cout << "Cannot add two Points!" << std::endl;
    return *this;
  }
}

bool MockTuple::operator==(const Tuple& other) const {
  return(x_ == other[0] && y_ == other[1] &&
    z_ == other[2] && w_ == other[3]);
}

MockTuple MockTuple::operator-(const MockTuple& other) const {
  return MockTuple(x_ - other[0], y_ - other[1],
    z_ - other[2], w_ - other[3]);
}

MockTuple MockTuple::operator-() const {
  return MockTuple(-x_, -y_, -z_, -w_);
}

MockTuple MockTuple::operator*(const float& scalar) const {
  return MockTuple(x_ * scalar, y_ * scalar,
    z_ * scalar, w_ * scalar);
}

MockTuple MockTuple::operator/(const float& scalar) const {
  return MockTuple(x_ / scalar, y_ / scalar,
    z_ / scalar, w_ / scalar);
}