#include "gradient-pattern.h"

GradientPattern::GradientPattern(const Color& a, const Color& b)
  : Pattern(a, b) {}

Color GradientPattern::pattern_at(const Point& point) {
  auto a_variant = this->GetA();
  auto b_variant = this->GetB();
  Color colorA = (*(std::get_if<Color>(&a_variant)));
  Color colorB = (*(std::get_if<Color>(&b_variant)));

  Color distance = colorB - colorA;
  float fraction = point[0] - floor(point[0]);
  return colorA + distance * fraction;
}