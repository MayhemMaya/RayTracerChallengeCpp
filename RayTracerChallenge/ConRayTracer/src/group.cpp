#include "group.h"
#include "ray.h"
#include <stdexcept>

Group::Group(const std::string& name)
  : Shape(name, ObjectType::kGroup), children_({}) {}

Group::Group(const std::string& name, const std::vector<Shape*>& children)
  : Shape(name, ObjectType::kGroup) {
  this->AddChildren(children);
}

Group::Group(const std::string& name, const std::vector<Shape*>& children, const Material& material)
  : Shape(name, ObjectType::kGroup, material) {
  this->AddChildren(children);
}

Group::Group(const std::string& name, const std::vector<Shape*>& children, const Matrix4& transform)
  : Shape(name, ObjectType::kGroup, transform) {
  this->AddChildren(children);
}

Group::Group(const std::string& name, const std::vector<Shape*>& children, const Material& material, const Matrix4& transform)
  : Shape(name, ObjectType::kGroup, material, transform) {
  this->AddChildren(children);
}

Group::~Group() {
  for (int i = 0; i < children_.size(); i++) {
    children_[i].child = nullptr;
    delete children_[i].child;
  }
}

//bool Group::operator==(const Object& object) {
//  Group* other = (Group*)&object;
//  return(this->GetName() == other->GetName() &&
//    this->GetTransform() == other->GetTransform() &&
//    this->GetObjectType() == other->GetObjectType() &&
//    this->GetMaterial() == other->GetMaterial());
//}
//
//Group& Group::operator=(const Object& object) {
//  Group* other = (Group*)&object;
//  this->SetName(other->GetName());
//  this->SetObjectType(other->GetObjectType());
//  this->SetTransform(other->GetTransform());
//  this->SetMaterial(other->GetMaterial());
//  return *this;
//}

std::vector<GroupChild> Group::GetChildren() const {
  return children_;
}

void Group::AddChild(Shape* child) {
  if (child == nullptr) {
    throw std::invalid_argument("Error: Group child cannot be null.");
  }
  child->SetParent(this);
  GroupChild gc;
  gc.child = child;
  gc.transform = this->GetTransform() * child->GetTransform();
  children_.push_back(gc);
}

void Group::AddChildren(const std::vector<Shape*>& children) {
  for (auto& child : children) {
    this->AddChild(child);
  }
}

int Group::GetChildrenCount() const {
  return children_.size();
}

bool Group::isEmpty() const {
  return children_.size() == 0;
}

bool Group::ContainsChild(Shape* other) const {
  for (auto& child : children_) {
    if ((*child.child) == (*other)) {
      return true;
    }
  }
  return false;
}

void Group::RemoveChild(Shape* child) {
  for (int i = 0; i < children_.size(); i++) {
    if ((*children_[i].child) == (*child)) {
      children_[i].child = nullptr;
      children_.erase(children_.begin() + i);
    }
  }
}

std::vector<Intersection> Group::local_intersect(const utils::RayStruct& local_ray) {
  std::vector<Intersection> xs;
  for (auto& object : children_) {
    Ray local(local_ray);
    Ray transformedRay = local.transform(object.transform.inverse());
    std::vector<Intersection> child_xs = object.child->local_intersect(transformedRay.to_ray_struct());
    for (auto& child : child_xs) {
      xs.push_back(child);
    }
  }
  return Intersection::intersections(xs);
}

Vector Group::local_normal_at(const Point& local_point) const {
  throw std::invalid_argument("Error: Cannot call local_normal_at on a Group object.");
  return Vector(0, 0, 0);
}