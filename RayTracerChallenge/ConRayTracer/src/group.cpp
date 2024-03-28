#include "group.h"
#include "ray.h"
#include <stdexcept>


Group::Group()
  : Shape("group", ObjectType::kGroup), children_({}), bounds_(BoundingBox()) {}

Group::Group(const std::string& name)
  : Shape(name, ObjectType::kGroup), children_({}), bounds_(BoundingBox()) {}

Group::Group(const std::string& name, const std::vector<Shape*>& children)
  : Shape(name, ObjectType::kGroup), bounds_(BoundingBox()) {
  this->AddChildren(children);
}

Group::Group(const std::string& name, const std::vector<Shape*>& children, const Material& material)
  : Shape(name, ObjectType::kGroup, material), bounds_(BoundingBox()) {
  this->AddChildren(children);
}

Group::Group(const std::string& name, const std::vector<Shape*>& children, const Matrix4& transform)
  : Shape(name, ObjectType::kGroup, transform), bounds_(BoundingBox()) {
  this->AddChildren(children);
}

Group::Group(const std::string& name, const std::vector<Shape*>& children, const Material& material, const Matrix4& transform)
  : Shape(name, ObjectType::kGroup, material, transform), bounds_(BoundingBox()) {
  this->AddChildren(children);
}

Group::~Group() {
  for (int i = 0; i < children_.size(); i++) {
    children_[i] = nullptr; 
    delete children_[i];
  }
}

//bool Group::operator==(const Object& object) {
//  Group* other = (Group*)&object;
//  return(this->GetName() == other->GetName() &&
//    this->GetTransform() == other->GetTransform() &&
//    this->GetObjectType() == other->GetObjectType() &&
//    this->GetMaterial() == other->GetMaterial());
//}

//Group& Group::operator=(const Object& object) {
//  Group* other = (Group*)&object;
//  name_ = other->GetName();
//  type_ = other->GetObjectType();
//  transform_ = other->GetTransform();
//  material_ = other->GetMaterial();
//  parent_ = other->GetParent();
//
//  return *this;
//}

std::vector<Shape*> Group::GetChildren() const {
  return children_;
}

void Group::AddChild(Shape* child) {
  if (child == nullptr) {
    throw std::invalid_argument("Error: Group child cannot be null.");
  }

  child->SetParent(this);
  Matrix4 child_transform = this->GetTransform() * child->GetTransform();
  transform_inverses_.push_back(child_transform.inverse());
  child->SetMaterial(this->GetMaterial());
  this->extend_bounds(child);
  children_.push_back(child);
}

void Group::AddChildren(const std::vector<Shape*>& children) {
  if (children.size() == 0) {
    throw std::invalid_argument("Error: std::vector of Group children cannot be empty.");
  }

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
    if ((*child) == (*other)) {
      return true;
    }
  }
  return false;
}

bool Group::ContainsChildWithName(const std::string& name) const {
  for (auto& child : children_) {
    if ((*child).GetName() == name) {
      return true;
    }
  }
  return false;
}

void Group::RemoveChild(Shape* child) {
  for (int i = 0; i < children_.size(); i++) {
    if ((*children_[i]) == (*child)) {
      children_[i]->RemoveParent();
      children_[i] = nullptr;
      children_.erase(children_.begin() + i);
      transform_inverses_.erase(transform_inverses_.begin() + i);
    }
  }
}

std::vector<Intersection> Group::local_intersect(const utils::RayStruct& local_ray) {
  if (!intersects_bounds(local_ray)) {
    return {};
  }

  std::vector<Intersection> xs;
  for (int i = 0; i < children_.size(); i++) {
    Ray local(local_ray);
    Ray transformedRay = local.transform(transform_inverses_[i]);
    std::vector<Intersection> child_intersections = children_[i]->local_intersect(transformedRay.to_ray_struct());
    xs.insert(xs.end(), child_intersections.begin(), child_intersections.end());
  }
  return Intersection::intersections(xs);
}

Vector Group::local_normal_at(const Point& local_point, const Intersection& hit) const {
  throw std::invalid_argument("Error: Group local_normal_at cannot be called.");
}

BoundingBox Group::bounds() const {
  return bounds_;
}

void Group::extend_bounds(Shape* shape) {
  this->bounds_.merge(shape->bounds().transform(shape->GetTransform()));
}

bool Group::intersects_bounds(const utils::RayStruct& ray) {
  // using structured bindings here now.
  const auto [x_tmin, x_tmax] = utils::check_axis(ray.origin[0], ray.direction[0],
                                    bounds_.GetMinimum()[0], bounds_.GetMaximum()[0]);
  const auto [y_tmin, y_tmax] = utils::check_axis(ray.origin[1], ray.direction[1],
                                    bounds_.GetMinimum()[1], bounds_.GetMaximum()[1]);
  const auto [z_tmin, z_tmax] = utils::check_axis(ray.origin[2], ray.direction[2],
                                    bounds_.GetMinimum()[2], bounds_.GetMaximum()[2]);

  const auto tmin = std::max({ x_tmin, y_tmin, z_tmin });
  const auto tmax = std::min({ x_tmax, y_tmax, z_tmax });

  return tmin < tmax;
}

void Group::ListDetails() const {
  std::string parent_name = parent_ == nullptr ? "None" : parent_->GetName();
  std::cout << "Name: " << name_ << "\n"
    << "Type: " << this->GetObjectTypeName() << "\n"
    << "ID: " << this->GetID() << "\n"
    << "Transform:\n" << transform_.format()
    << "Parent: " << parent_name << "\n"
    << "Children Count: " << children_.size() << "\n";
}

void Group::SetMaterial(const Material& material) {
  material_ = material;

  if (children_.size() > 0) {
    for (auto& child : children_) {
      child->SetMaterial(this->GetMaterial());
    }
  }
}

void Group::SetTransform(const Matrix4& transform) {
  transform_ = transform_ * transform;
  cached_transform_inverse_ = transform_.inverse();

  if (children_.size() > 0) {
    for (int i = 0; i < children_.size(); i++) {
      Matrix4 child_transform = this->GetTransform() * children_[i]->GetTransform();
      transform_inverses_[i] = child_transform.inverse();
    }
  }
}