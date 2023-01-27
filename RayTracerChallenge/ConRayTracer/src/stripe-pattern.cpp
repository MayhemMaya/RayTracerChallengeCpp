#include "stripe-pattern.h"

StripePattern::StripePattern(const Color& a, const Color& b)
  : Pattern(a, b){}

StripePattern::StripePattern(Pattern* a, Pattern* b)
  : Pattern(a, b) {}

Color StripePattern::pattern_at(const Point& point) {
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

  if ((int)floor(point[0]) % 2 == 0) {
    return colorA;
  }
  return colorB;
}