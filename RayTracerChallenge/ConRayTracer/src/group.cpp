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
    children_[i].object = nullptr;
    delete children_[i].object;
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
  gc.object = child;
  gc.transform = this->GetTransform() * child->GetTransform();
  gc.transform_inverse = gc.transform.inverse();
  gc.original_mat = child->GetMaterial();
  child->SetMaterial(this->GetMaterial());
  this->extend_bounds(child);
  children_.push_back(gc);
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
    if ((*child.object) == (*other)) {
      return true;
    }
  }
  return false;
}

void Group::RemoveChild(Shape* child) {
  for (int i = 0; i < children_.size(); i++) {
    if ((*children_[i].object) == (*child)) {
      children_[i].object->RemoveParent();
      children_[i].object->SetMaterial(children_[i].original_mat);
      children_[i].object = nullptr;
      children_.erase(children_.begin() + i);
    }
  }
}

std::vector<Intersection> Group::local_intersect(const utils::RayStruct& local_ray) {
  if (!intersects_bounds(local_ray)) {
    return {};
  }

  std::vector<Intersection> xs;
  for (auto& child : children_) {
    Ray local(local_ray);
    Ray transformedRay = local.transform(child.transform_inverse);
    std::vector<Intersection> child_intersections = child.object->local_intersect(transformedRay.to_ray_struct());
    xs.insert(xs.end(), child_intersections.begin(), child_intersections.end());
  }
  return Intersection::intersections(xs);
}

Vector Group::local_normal_at(const Point& local_point) const {
  throw std::invalid_argument("Error: Group local_normal_at cannot be called.");
}

BoundingBox Group::bounds() const {
  return bounds_;
}

void Group::extend_bounds(Shape* shape) {
  this->bounds_.merge(shape->bounds().transform(shape->GetTransform()));
}

bool Group::intersects_bounds(const utils::RayStruct& ray) {
  utils::TimeValuePair x = utils::check_axis(ray.origin[0], ray.direction[0],
                                    bounds_.GetMinimum()[0], bounds_.GetMaximum()[0]);
  utils::TimeValuePair y = utils::check_axis(ray.origin[1], ray.direction[1],
                                    bounds_.GetMinimum()[1], bounds_.GetMaximum()[1]);
  utils::TimeValuePair z = utils::check_axis(ray.origin[2], ray.direction[2],
                                    bounds_.GetMinimum()[2], bounds_.GetMaximum()[2]);

  auto tmin = std::max({ x.tmin, y.tmin, z.tmin });
  auto tmax = std::min({ x.tmax, y.tmax, z.tmax });

  return tmin < tmax;
}