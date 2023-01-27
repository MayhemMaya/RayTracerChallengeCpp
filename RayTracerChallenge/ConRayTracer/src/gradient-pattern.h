#pragma once

#include "pattern.h"

class GradientPattern : public Pattern {
public:
  GradientPattern(const Color& a, const Color& b);
  Color pattern_at(const Point& point) override;
};