
#include <iostream>
#include "projectile.h"

Projectile::Projectile(Point position, Vector velocity) 
    : position_(position), velocity_(velocity) {}

Point Projectile::GetPosition() const { return position_; }
Vector Projectile::GetVelocity() const { return velocity_; }

std::ostream& operator<<(std::ostream& os, const Projectile& obj) {
  os << "Position: " << obj.position_ << " " << "Velocity: " << obj.velocity_;
  return os;
}