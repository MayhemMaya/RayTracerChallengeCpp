#pragma once

#include <iostream>
#include "point.h"
#include "vector.h"

class Projectile {
 public:
  Projectile(const Point& position, const Vector& velocity);
  Point GetPosition() const;
  Vector GetVelocity() const;
  friend std::ostream& operator<<(std::ostream& os, const Projectile& obj);
 private:
  Point position_;
  Vector velocity_;
};
