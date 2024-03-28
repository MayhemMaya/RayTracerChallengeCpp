#include "mock-shape.h"

MockShape::MockShape(const std::string& name) : Shape(name, ObjectType::kShape) {
}

bool MockShape::operator==(const Object& object) const {
  MockShape* other = (MockShape*)&object;
  return(name_ == other->GetName() &&
    transform_ == other->GetTransform() &&
    type_ == other->GetObjectType() &&
    id_ == other->GetID() &&
    material_ == other->GetMaterial() &&
    parent_ == other->GetParent());
}

MockShape& MockShape::operator=(const Object& object) {
  MockShape* other = (MockShape*)&object;
  name_ = other->GetName();
  type_ = other->GetObjectType();
  transform_ = other->GetTransform();
  material_ = other->GetMaterial();
  parent_ = other->GetParent();
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

Vector MockShape::local_normal_at(const Point& local_point, const Intersection& hit) const {
  return Vector(local_point[0], local_point[1], local_point[2]);
}

BoundingBox MockShape::bounds() const {
  return BoundingBox(Point(-1.0f, -1.0f, -1.0f), Point(1.0f, 1.0f, 1.0f));;
}