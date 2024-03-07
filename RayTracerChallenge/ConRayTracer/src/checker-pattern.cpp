#include "checker-pattern.h"

CheckerPattern::CheckerPattern(const Color& a, const Color& b)
  : Pattern(a, b) {}

CheckerPattern::CheckerPattern(Pattern* a, Pattern* b)
  : Pattern(a, b) {}

Color CheckerPattern::pattern_at(const Point& point) {
  Color colorA, colorB;
  auto a_variant = this->GetA();
  auto b_variant = this->GetB();

  if (this->holdsNestedPattern()) {
    Pattern* a (*(std::get_if<Pattern*>(&a_variant)));
    Point nested_a_pattern_point = a->GetTransform().inverse() * point;
    colorA = a->pattern_at(nested_a_pattern_point);
    Pattern* b (*(std::get_if<Pattern*>(&b_variant)));
    Point nested_b_pattern_point = b->GetTransform().inverse() * point;
    colorB = b->pattern_at(nested_b_pattern_point);
  }
  else {
    colorA = (*(std::get_if<Color>(&a_variant)));
    colorB = (*(std::get_if<Color>(&b_variant)));
  }

  if ((int)(floor(point[0]) + floor(point[1]) + floor(point[2])) % 2 == 0) {
    return colorA;
  }
  return colorB;
}