#include "pattern.h"

Pattern::Pattern(const Color& a, const Color& b)
  : a_(std::in_place_index<0>, a), b_(std::in_place_index<0>, b), saved_transform_inverse_(transform_.inverse()) {}
Pattern::Pattern(Pattern* a, Pattern* b)
  : a_(std::in_place_index<1>, a), b_(std::in_place_index<1>, b), saved_transform_inverse_(transform_.inverse()) {}

Pattern::~Pattern() {}

Color Pattern::pattern_at_object(Object* object, const Point& world_point) {
  Point object_point = object->GetSavedTransformInverse() * world_point;
  Point pattern_point = this->transform_.inverse() * object_point;
  Color color = this->pattern_at(pattern_point);
  return color;
}

void Pattern::SetTransform(const Matrix4& transform) {
  this->transform_ = this->transform_ * transform;
  this->saved_transform_inverse_ = this->transform_.inverse();
}
Matrix4 Pattern::GetTransform() const {
  return this->transform_;
}

std::variant<Color, Pattern*> Pattern::GetA() const {
  return a_;
}

std::variant<Color, Pattern*> Pattern::GetB() const {
  return b_;
}

bool Pattern::holdsNestedPattern() const {
  if (std::holds_alternative<Pattern*>(a_) && std::holds_alternative<Pattern*>(b_)) {
    return true;
  }
  return false;
}

bool Pattern::operator==(const Pattern& other) const {
  return a_ == other.a_ && b_ == other.b_ && transform_ == other.transform_;
}

Matrix4 Pattern::GetSavedTransformInverse() const {
  return saved_transform_inverse_;
}