#include "mock-pattern.h"

MockPattern::MockPattern() : Pattern(Colors::White, Colors::Black) {}

Color MockPattern::pattern_at(const Point& point) {
  return Color(point[0], point[1], point[2]);
}
