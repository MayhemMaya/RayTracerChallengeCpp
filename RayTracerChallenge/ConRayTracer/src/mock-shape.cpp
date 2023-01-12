#include "mock-shape.h"

MockShape::MockShape() : Shape("shape", ObjectType::kShape) {}

MockShape::MockShape(const std::string& name) : Shape(name, ObjectType::kShape) {}

bool MockShape::operator==(const Object& object) const {
  MockShape* other = (MockShape*)&object;
  return(this->GetName() == other->GetName() &&
    this->GetTransform() == other->GetTransform() &&
    this->GetObjectType() == other->GetObjectType() &&
    this->GetMaterial() == other->GetMaterial());
}

MockShape& MockShape::operator=(const Object& object) {
  MockShape* other = (MockShape*)&object;
  this->SetName(other->GetName());
  this->SetObjectType(other->GetObjectType());
  this->SetTransform(other->GetTransform());
  this->SetMaterial(other->GetMaterial());
  return *this;
}

utils::RayStruct MockShape::GetSavedRay() const {
  return saved_ray_;
}

void MockShape::SetSavedRay(const Point& origin, const Vector& direction) {
  saved_ray_.origin = origin;
  saved_ray_.direction = direction;
}

std::vector<Intersection> MockShape::local_intersect(const utils::RayStruct& local_ray) {
  std::vector<Intersection> intersections;
  this->SetSavedRay(local_ray.origin, local_ray.direction);
  return intersections;
}

Vector MockShape::local_normal_at(const Point& local_point) const {
  return Vector(local_point[0], local_point[1], local_point[2]);
}