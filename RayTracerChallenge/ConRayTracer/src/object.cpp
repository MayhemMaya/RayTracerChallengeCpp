#include "object.h"

int Object::object_count_ = 0;

Object::Object(const std::string& name, const ObjectType& type)
    : transform_(Matrix4()), name_(name), type_(type), parent_(nullptr) {
      object_count_++;
}

Object::Object(const std::string& name, const ObjectType& type, const Matrix4& transform)
  : transform_(transform), name_(name), type_(type), parent_(nullptr) {
  object_count_++;
}

Object::Object(const std::string& name, const ObjectType& type, const Point& position)
    : transform_(Matrix4().translation(position[0], position[1], position[2])), 
      name_(name), type_(type), parent_(nullptr) {
  object_count_++;
}

Object::~Object() {
  object_count_--;
  parent_ = nullptr;
  delete parent_;
}

void Object::ListDetails() {
  std::string parent_name = parent_ == nullptr ? "None" : parent_->GetName();
  std::cout << "Name: " << name_ << "\n"
      << "Type: " << this->GetObjectTypeName() << "\n"
      << "Transform:\n" << transform_.format() << "\n"
      << "Parent:\n" << parent_name << "\n";
}

std::string Object::GetName() const { return name_; }

void Object::SetName(const std::string& name) { name_ = name; }

Matrix4 Object::GetTransform() const { return transform_; }

void Object::SetTransform(const Matrix4& transform) {
  transform_ = transform_ * transform;
}

void Object::SetObjectType(const ObjectType& type) {
  type_ = type;
}

Object* Object::GetParent() const {
  return parent_;
}

void Object::SetParent(Object* parent) {
  if (parent == this) {
    throw std::invalid_argument("Error: Object's parent cannot be itself.");
  }

  if (parent == nullptr) {
    throw std::invalid_argument("Error: Object's parent cannot be null.");
  }

  parent_ = parent;
}

void Object::RemoveParent() {
  if (parent_ == nullptr) {
    throw std::invalid_argument("Error: No parent to remove from object");
  }
  parent_ = nullptr;
}

bool Object::HasParent() const {
  return parent_ != nullptr;
}

Point Object::GetPosition() const {
  float x = transform_(0, 3);
  float y = transform_(1, 3);
  float z = transform_(2, 3);
  return Point(x, y, z);
}

ObjectType Object::GetObjectType() const { return type_; }

std::string Object::GetObjectTypeName() const {
  return typeMap[type_];
}

bool Object::operator==(const Object& other) {
  return(name_ == other.GetName() &&
         transform_ == other.GetTransform() &&
         type_ == other.GetObjectType());
}

Object& Object::operator=(const Object& other) {
  name_ = other.GetName();
  type_ = other.GetObjectType();
  transform_ = other.GetTransform();
  return *this;
}

int Object::GetCount() { return object_count_; }

Point Object::world_to_object(const Object* shape, Point point) {
  if (shape->HasParent()) {
    point = Object::world_to_object(shape->GetParent(), point);
  }
  return shape->GetTransform().inverse() * point;
}