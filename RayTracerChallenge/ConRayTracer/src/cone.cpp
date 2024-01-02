#include "cone.h"
#include <limits>
#include <algorithm>
#include <cmath>


Cone::Cone(float minimum, float maximum, bool closed)
  : Shape("cone", ObjectType::kCone),
  minimum_(minimum), maximum_(maximum), closed_(closed) {}

Cone::Cone(const std::string& name, float minimum, float maximum, bool closed)
  : Shape(name, ObjectType::kCone),
  minimum_(minimum), maximum_(maximum), closed_(closed) {}

Cone::Cone(const Material& material, float minimum, float maximum, bool closed)
  : Shape("cone", ObjectType::kCone, material),
  minimum_(minimum), maximum_(maximum), closed_(closed) {}

Cone::Cone(const Matrix4& transform, float minimum, float maximum, bool closed)
  : Shape("cone", ObjectType::kCone, transform),
  minimum_(minimum), maximum_(maximum), closed_(closed) {}

Cone::Cone(const std::string& name, const Material& material, float minimum, float maximum, bool closed)
  : Shape(name, ObjectType::kCone, material),
  minimum_(minimum), maximum_(maximum), closed_(closed) {}

Cone::Cone(const std::string& name, const Matrix4& transform, float minimum, float maximum, bool closed)
  : Shape(name, ObjectType::kCone, transform),
  minimum_(minimum), maximum_(maximum), closed_(closed) {}

Cone::Cone(const Material& material, const Matrix4& transform, float minimum, float maximum, bool closed)
  : Shape("cone", ObjectType::kCone, material, transform),
  minimum_(minimum), maximum_(maximum), closed_(closed) {}

Cone::Cone(const std::string& name, const Material& material, const Matrix4& transform, float minimum, float maximum, bool closed)
  : Shape(name, ObjectType::kCone, material, transform),
  minimum_(minimum), maximum_(maximum), closed_(closed) {}

bool Cone::operator==(const Object& object) {
  Cone* other = (Cone*)&object;
  return(this->GetName() == other->GetName() &&
    this->GetTransform() == other->GetTransform() &&
    this->GetObjectType() == other->GetObjectType() &&
    this->GetMaterial() == other->GetMaterial());
}

Cone& Cone::operator=(const Object& object) {
  Cone* other = (Cone*)&object;
  this->SetName(other->GetName());
  this->SetObjectType(other->GetObjectType());
  this->SetTransform(other->GetTransform());
  this->SetMaterial(other->GetMaterial());
  return *this;
}

std::vector<Intersection> Cone::local_intersect(const utils::RayStruct& local_ray) {
  std::vector<Intersection> xs;

  const auto origin_x = local_ray.origin[0];
  const auto direction_x = local_ray.direction[0];
  const auto origin_y = local_ray.origin[1];
  const auto direction_y = local_ray.direction[1];
  const auto origin_z = local_ray.origin[2];
  const auto direction_z = local_ray.direction[2];

  const auto a = pow(direction_x, 2) - pow(direction_y, 2) + pow(direction_z, 2);
  const auto b = 2 * origin_x * direction_x - 2 * origin_y * direction_y + 2 * origin_z * direction_z;
  const auto c = pow(origin_x, 2) - pow(origin_y, 2) + pow(origin_z, 2);
  const auto discriminant = (b * b) - 4.0f * a * c;

  // When a is zero, it means the ray is parallel to one of the cone’s halves
  // this still means the ray might intersect the other half of the cone.
  if (utils::equal(a, 0)) {
    if (!utils::equal(b, 0)) {
      const auto t = -c / (2 * b);
      xs.push_back(Intersection(t, this));
    }
  }

  // In general, the discriminant of the quadratic equation should be non-negative if there are real solutions, 
  // and negative if there are complex solutions. However, due to floating-point roundoff errors, the discriminant 
  // may sometimes become slightly negative even when there are real solutions, leading to incorrect results.
  // Here, rel_eps is a small relative epsilon based on the magnitudes of the coefficients, making it more robust to0
  // different combinations of coefficients
  const float eps = 0.000001f;
  const auto rel_eps = eps * std::max<double>({ abs(a), abs(b), abs(c) });

  // ray does not intersect the cone
  if (discriminant < -rel_eps) { //The discriminant is considered to be negative if it is less than -rel_ep
    return {};
  }

  const auto sqrt_discriminant = sqrt(std::max(discriminant, 0.0)); //round to 0 if need be.

  auto t0 = (-b - sqrt_discriminant) / (2 * a);
  auto t1 = (-b + sqrt_discriminant) / (2 * a);

  //if (t0 > t1) {
  //  auto temp = t0;
  //  t0 = t1;
  //  t1 = temp;
  //}

  //xs = {};

  const auto y0 = origin_y + t0 * direction_y;
  const auto y1 = origin_y + t1 * direction_y;

  if (this->minimum_ < y0 && y0 < this->maximum_) {
    xs.push_back(Intersection(t0, this));
  }

  if (this->minimum_ < y1 && y1 < this->maximum_) {
    xs.push_back(Intersection(t1, this));
  }

  this->intersect_caps(local_ray, xs);

  return xs;
}

Vector Cone::local_normal_at(const Point& local_point) const {
  // compute the square of the distance from the y axis
  const auto dist = pow(local_point[0], 2) + pow(local_point[2], 2);

  if (dist < 1 && local_point[1] >= this->maximum_ - utils::kEPSILON) {
    return Vector(0, 1, 0);
  }
  else if (dist < 1 && local_point[1] <= this->minimum_ + utils::kEPSILON) {
    return Vector(0, -1, 0);
  }

  float y = sqrt((pow(local_point[0], 2) + pow(local_point[2], 2)));
  if (local_point[1] > 0) y = -y;

  return Vector(local_point[0], y, local_point[2]);
}

float Cone::GetMinimum() const { return minimum_; }

float Cone::GetMaximum() const { return maximum_; }

bool Cone::GetClosed() const { return closed_; }

void Cone::SetMinimum(float minimum) {
  minimum_ = minimum;
}

void Cone::SetMaximum(float maximum) {
  maximum_ = maximum;
}

void Cone::SetClosed(bool closed) {
  closed_ = closed;
}

void Cone::intersect_caps(const utils::RayStruct& local_ray, std::vector<Intersection>& xs) {

  // caps only matter if the cone is closed, and might possibly be
  // intersected by the ray.
  if (this->closed_ == false || utils::is_close_to_zero(local_ray.direction[1])) return;

  // check for an intersection with the lower end cap by intersecting
  // the ray with the plane at y = cyl.minimum
  const auto lower_t = (this->minimum_ - local_ray.origin[1]) / local_ray.direction[1];

  if (utils::check_cone_cap(local_ray, lower_t, this->minimum_)) {
    xs.push_back(Intersection(lower_t, this));
  }

  // check for an intersection with the upper end cap by intersecting
  // the ray with the plane at y = cyl.maximum
  const auto upper_t = (this->maximum_ - local_ray.origin[1]) / local_ray.direction[1];

  if (utils::check_cone_cap(local_ray, upper_t, this->maximum_)) {
    xs.push_back(Intersection(upper_t, this));
  }
}