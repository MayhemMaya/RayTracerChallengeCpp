#pragma once

#include "pattern.h"

class CheckerPattern : public Pattern {
public:
  CheckerPattern(const Color& a, const Color& b);
  CheckerPattern(Pattern* a, Pattern* b);
  Color pattern_at(const Point& point) override;
};