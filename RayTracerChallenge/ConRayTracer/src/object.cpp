#include "object.h"
#include "translation-matrix.h"

int Object::object_count_ = 0;

Object::Object(std::string name)
    : transform_(Matrix4()), name_(name) {
  object_count_++;
}

Object::Object(std::string name, const Point& position)
    : transform_(TranslationMatrix(position[0], position[1], position[2])), name_(name) {
  object_count_++;
}

Object::~Object() {
  object_count_--;
}

std::string Object::GetName() const {
  return name_;
}

void Object::SetName(const std::string& name) {
  name_ = name;
}

Matrix4 Object::GetTransform() const {
  return transform_;
}

void Object::SetTransform(const Matrix4& transform) {
  transform_ = transform_ * transform;
}

Point Object::GetPosition() const {
  float x = transform_(0, 3);
  float y = transform_(1, 3);
  float z = transform_(2, 3);
  return Point(x, y, z);
}
bool Object::operator==(const Object& other) const {
  return(name_ == other.GetName() && transform_ == other.GetTransform());
}

int Object::GetCount() { return object_count_; }