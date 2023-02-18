#include "object.h"

int Object::object_count_ = 0;

Object::Object(const std::string& name, const ObjectType& type)
    : transform_(Matrix4()), name_(name), type_(type), saved_transform_inverse_(transform_.inverse()) {
      object_count_++;
}

Object::Object(const std::string& name, const ObjectType& type, const Matrix4& transform)
  : transform_(transform), name_(name), type_(type), saved_transform_inverse_(transform_.inverse()) {
  object_count_++;
}

Object::Object(const std::string& name, const ObjectType& type, const Point& position)
    : transform_(Matrix4().translation(position[0], position[1], position[2])), 
      name_(name), type_(type), saved_transform_inverse_(transform_.inverse()) {
  object_count_++;
}

Object::~Object() {
  object_count_--;
}

void Object::ListDetails() {
  std::cout << "Name: " << name_ << "\n"
      << "Type: " << this->GetObjectTypeName() << "\n"
      << "Transform:\n" << transform_.format() << std::endl;
}

std::string Object::GetName() const { return name_; }

void Object::SetName(const std::string& name) { name_ = name; }

Matrix4 Object::GetTransform() const { return transform_; }

void Object::SetTransform(const Matrix4& transform) {
  transform_ = transform_ * transform;
  saved_transform_inverse_ = transform_.inverse();
}

void Object::SetObjectType(const ObjectType& type) {
  type_ = type;
}

Matrix4 Object::GetSavedTransformInverse() const {
  return saved_transform_inverse_;
}

Point Object::GetPosition() const {
  float x = transform_(0, 3);
  float y = transform_(1, 3);
  float z = transform_(2, 3);
  return Point(x, y, z);
}

ObjectType Object::GetObjectType() const { return type_; }

std::string Object::GetObjectTypeName() const {
  std::string type_name = type_names[static_cast<int>(type_)];
  std::string first_letter = type_name.substr(0, 1);
  std::transform(first_letter.begin(), first_letter.end(), first_letter.begin(), ::toupper);
  return "k" + first_letter + type_name.substr(1);
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