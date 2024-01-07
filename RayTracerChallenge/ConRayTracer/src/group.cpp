#include "group.h"

Group::Group(const std::string& name)
  : Shape(name, ObjectType::kGroup), children_({}) {}

Group::Group(const std::string& name, const std::vector<Shape*>& children)
  : Shape(name, ObjectType::kGroup), children_(children) {}

Group::Group(const std::string& name, const std::vector<Shape*>& children, const Material& material)
  : Shape(name, ObjectType::kGroup, material), children_(children) {}

Group::Group(const std::string& name, const std::vector<Shape*>& children, const Matrix4& transform)
  : Shape(name, ObjectType::kGroup, transform), children_(children) {}

Group::Group(const std::string& name, const std::vector<Shape*>& children, const Material& material, const Matrix4& transform)
  : Shape(name, ObjectType::kGroup, material, transform), children_(children) {}

Group::~Group() {
  for (int i = 0; i < children_.size(); i++) {
    children_[i] = nullptr;
    delete children_[i];
  }
}

bool Group::operator==(const Object& object) {
  Group* other = (Group*)&object;
  return(this->GetName() == other->GetName() &&
    this->GetTransform() == other->GetTransform() &&
    this->GetObjectType() == other->GetObjectType() &&
    this->GetMaterial() == other->GetMaterial());
}

Group& Group::operator=(const Object& object) {
  Group* other = (Group*)&object;
  this->SetName(other->GetName());
  this->SetObjectType(other->GetObjectType());
  this->SetTransform(other->GetTransform());
  this->SetMaterial(other->GetMaterial());
  return *this;
}

std::vector<Shape*> Group::GetChildren() const {
  return children_;
}

void Group::AddChildren(std::vector<Shape*> children) {
  for (auto& child : children) {
    children_.push_back(child);
  }
}

int Group::GetChildrenCount() const {
  return children_.size();
}

std::vector<Intersection> Group::local_intersect(const utils::RayStruct& local_ray) {
  return {};
}

Vector Group::local_normal_at(const Point& local_point) const {
  return Vector(0, 0, 0);
}