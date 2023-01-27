#pragma once

#include "pattern.h"

class RadialGradientPattern : public Pattern {
public:
  RadialGradientPattern(const Color& a, const Color& b);
  Color pattern_at(const Point& point) override;
};