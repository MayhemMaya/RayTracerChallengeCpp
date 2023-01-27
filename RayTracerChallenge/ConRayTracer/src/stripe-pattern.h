#pragma once

#include "pattern.h"

class StripePattern : public Pattern {
public:
  StripePattern(const Color& a, const Color& b);
  StripePattern(Pattern* a, Pattern* b);
  Color pattern_at(const Point& point) override;
};