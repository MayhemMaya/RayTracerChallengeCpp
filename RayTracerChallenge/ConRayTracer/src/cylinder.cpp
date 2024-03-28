#include "cylinder.h"
#include <limits>
#include <algorithm>

Cylinder::Cylinder()
  : Shape("cylinder", ObjectType::kCylinder),
    minimum_(-utils::kINFINITY), maximum_(utils::kINFINITY), closed_(false) {}

Cylinder::Cylinder(const std::string& name, float minimum, float maximum, bool closed)
  : Shape(name, ObjectType::kCylinder),
  minimum_(minimum), maximum_(maximum), closed_(closed) {}

Cylinder::Cylinder(const std::string& name, const Material& material, float minimum, float maximum, bool closed)
  : Shape(name, ObjectType::kCylinder, material),
    minimum_(minimum), maximum_(maximum), closed_(closed) {}

Cylinder::Cylinder(const std::string& name, const Matrix4& transform, float minimum, float maximum, bool closed)
  : Shape(name, ObjectType::kCylinder, transform),
    minimum_(minimum), maximum_(maximum), closed_(closed) {}

Cylinder::Cylinder(const std::string& name, const Material& material, const Matrix4& transform, float minimum, float maximum, bool closed)
  : Shape(name, ObjectType::kCylinder, material, transform),
    minimum_(minimum), maximum_(maximum), closed_(closed) {}

bool Cylinder::operator==(const Object& object) const {
  Cylinder* other = (Cylinder*)&object;
  return(name_ == other->GetName() &&
    transform_ == other->GetTransform() &&
    type_ == other->GetObjectType() &&
    parent_ == other->GetParent() &&
    id_ == other->GetID() &&
    material_ == other->GetMaterial() &&
    minimum_ == other->minimum_ &&
    maximum_ == other->maximum_ &&
    closed_ == other->closed_);
}

Cylinder& Cylinder::operator=(const Object& object) {
  Cylinder* other = (Cylinder*)&object;
  name_ = other->GetName();
  type_ = other->GetObjectType();
  transform_ = other->GetTransform();
  material_ = other->GetMaterial();
  parent_ = other->GetParent();
  minimum_ = other->minimum_;
  maximum_ = other->maximum_;
  closed_ = other->closed_;
  return *this;
}

std::vector<Intersection> Cylinder::local_intersect(const utils::RayStruct& local_ray) {
  std::vector<Intersection> xs;

  const auto origin_x = local_ray.origin[0];
  const auto direction_x = local_ray.direction[0];
  const auto origin_y = local_ray.origin[1];
  const auto direction_y = local_ray.direction[1];
  const auto origin_z = local_ray.origin[2];
  const auto direction_z = local_ray.direction[2];

  const auto a = pow(direction_x, 2) + pow(direction_z, 2);
  const auto b = 2 * origin_x * direction_x + 2 * origin_z * direction_z;
  const auto c = pow(origin_x, 2) + pow(origin_z, 2) - 1;
  const auto discriminant = (b * b) - 4.0f * a * c;

  // ray is parallel to the y axis
  if (utils::is_close_to_zero(a)) {
    this->intersect_caps(local_ray, xs);
    return xs;
  }

  // ray does not intersect the cylinder
  if (discriminant < 0) {
    return {};
  }

  auto t0 = (-b - sqrt(discriminant)) / (2 * a);
  auto t1 = (-b + sqrt(discriminant)) / (2 * a);

  if (t0 > t1) {
    auto temp = t0;
    t0 = t1;
    t1 = temp;
  }

  xs = {};

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

Vector Cylinder::local_normal_at(const Point& local_point, const Intersection& hit) const {
  // compute the square of the distance from the y axis
  const auto dist = pow(local_point[0], 2) + pow(local_point[2], 2);

  if (dist < 1 && local_point[1] >= this->maximum_ - utils::kEPSILON) {
    return Vector(0, 1, 0);
  }
  else if (dist < 1 && local_point[1] <= this->minimum_ + utils::kEPSILON) {
    return Vector(0, -1, 0);
  }
  return Vector(local_point[0], 0, local_point[2]);
}

float Cylinder::GetMinimum() const { return minimum_; }

float Cylinder::GetMaximum() const { return maximum_; }

bool Cylinder::GetClosed() const { return closed_; }

void Cylinder::SetMinimum(float minimum) {
  minimum_ = minimum;
}

void Cylinder::SetMaximum(float maximum) {
  maximum_ = maximum;
}

void Cylinder::SetClosed(bool closed) {
  closed_ = closed;
}

void Cylinder::intersect_caps(const utils::RayStruct& local_ray, std::vector<Intersection>& xs) {
  
  // caps only matter if the cylinder is closed, and might possibly be
  // intersected by the ray.
  if (this->closed_ == false || utils::is_close_to_zero(local_ray.direction[1])) return;

  // check for an intersection with the lower end cap by intersecting
  // the ray with the plane at y = cyl.minimum
  const auto lower_t = (this->minimum_ - local_ray.origin[1]) / local_ray.direction[1];

  if (utils::check_cylinder_cap(local_ray, lower_t)) {
    xs.push_back(Intersection(lower_t, this));
  }

  // check for an intersection with the upper end cap by intersecting
  // the ray with the plane at y = cyl.maximum
  const auto upper_t = (this->maximum_ - local_ray.origin[1]) / local_ray.direction[1];

  if (utils::check_cylinder_cap(local_ray, upper_t)) {
    xs.push_back(Intersection(upper_t, this));
  }
}

BoundingBox Cylinder::bounds() const {
  return BoundingBox(Point(-1.0f, minimum_, -1.0f), Point(1.0f, maximum_, 1.0f));;
}