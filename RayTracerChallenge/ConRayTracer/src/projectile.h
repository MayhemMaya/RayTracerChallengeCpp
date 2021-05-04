#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <iostream>
#include "point.h"
#include "vector.h"

class Projectile {
 public:
  Projectile(Point position, Vector velocity);
  Point GetPosition() const;
  Vector GetVelocity() const;
  friend std::ostream& operator<<(std::ostream& os, const Projectile& obj);
 private:
  Point position_;
  Vector velocity_;
};

#endif // PROJECTILE_H