#pragma once

#include "color.h"
#include "point.h"
#include "object.h"
#include <variant>

class Pattern {
public:
  Pattern(const Color& a, const Color& b);
  Pattern(Pattern* a, Pattern* b);
  virtual ~Pattern() = 0;
  virtual Color pattern_at(const Point& point) = 0;
  Color pattern_at_object(Object* object, const Point& world_point);
  void SetTransform(const Matrix4& transform);
  Matrix4 GetTransform() const;
  Matrix4 GetCachedTransformInverse() const;
  std::variant<Color, Pattern*> GetA() const;
  std::variant<Color, Pattern*> GetB() const;
  bool holdsNestedPattern() const;
  virtual bool operator==(const Pattern& other) const;
private:
  std::variant<Color, Pattern*> a_, b_;
  Matrix4 transform_;
  Matrix4 cached_transform_inverse_;
};