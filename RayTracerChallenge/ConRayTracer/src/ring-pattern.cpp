#include "ring-pattern.h"

RingPattern::RingPattern(const Color& a, const Color& b)
  : Pattern(a, b) {}

RingPattern::RingPattern(Pattern* a, Pattern* b)
  : Pattern(a, b) {}

Color RingPattern::pattern_at(const Point& point) {
  Color colorA, colorB;
  auto a_variant = this->GetA();
  auto b_variant = this->GetB();

  if (this->holdsNestedPattern()) {
    Pattern* a(*(std::get_if<Pattern*>(&a_variant)));
    colorA = a->pattern_at(point);
    Pattern* b(*(std::get_if<Pattern*>(&b_variant)));
    colorB = b->pattern_at(point);
  }
  else {
    colorA = (*(std::get_if<Color>(&a_variant)));
    colorB = (*(std::get_if<Color>(&b_variant)));
  }

  if ((int)floor(sqrt(pow(point[0], 2) + pow(point[2], 2))) % 2 == 0) {
    return colorA;
  }
  return colorB;
}