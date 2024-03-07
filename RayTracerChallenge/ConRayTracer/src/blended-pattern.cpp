#include "blended-pattern.h"

BlendedPattern::BlendedPattern(Pattern* a, Pattern* b)
  : Pattern(a, b) {}

Color BlendedPattern::pattern_at(const Point& point) {
  auto a_variant = this->GetA();
  auto b_variant = this->GetB();

  Pattern* a(*(std::get_if<Pattern*>(&a_variant)));
  Point nested_a_pattern_point = a->GetCachedTransformInverse() * point;
  Color colorA = a->pattern_at(nested_a_pattern_point);
  Pattern* b(*(std::get_if<Pattern*>(&b_variant)));
  Point nested_b_pattern_point = b->GetCachedTransformInverse() * point;
  Color colorB = b->pattern_at(nested_b_pattern_point);

  Color average = (colorA + colorB) / 2;
  return average;
}