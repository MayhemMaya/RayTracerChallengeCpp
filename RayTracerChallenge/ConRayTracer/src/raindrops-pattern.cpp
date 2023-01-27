#include "raindrops-pattern.h"

RainDropsPattern::RainDropsPattern(const Color& a, const Color& b)
  : Pattern(a, b) {}

Color RainDropsPattern::pattern_at(const Point& point) {
  auto a_variant = this->GetA();
  auto b_variant = this->GetB();
  Color colorA = (*(std::get_if<Color>(&a_variant)));
  Color colorB = (*(std::get_if<Color>(&b_variant)));

  Color distance = colorB - colorA;
  float fraction = sqrt(point[0] + point[2]) - floor(sqrt(point[0] + point[2]));
  return colorA + distance * fraction;
}