#include <sstream>
#include "object.h"

int Object::object_count_ = 0;

Object::Object()
    : transform_(Matrix4()), name_("object") {
  object_count_++;
  std::stringstream ss;
  ss << object_count_;
  name_ += ss.str();
}


Object::Object(std::string name)
    : transform_(Matrix4()), name_(name) {
  object_count_++;
  if (name == "sphere") {
    std::stringstream ss;
    ss << object_count_;
    name_ += ss.str();
  }
}

std::ostream& operator<<(std::ostream& os, const Object& obj) {
  os << "Name: " << obj.name_ << " Transform: "; // << obj.transform_;
  return os;
}

std::string Object::GetName() const {
  return name_;
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
  return(name_ == other.GetName()); //&& transform_ == other.GetTransform());
}