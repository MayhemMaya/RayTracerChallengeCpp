#pragma once

#include "pattern.h"

class RingPattern : public Pattern {
public:
  RingPattern(const Color& a, const Color& b);
  RingPattern(Pattern* a, Pattern* b);
  Color pattern_at(const Point& point) override;
};