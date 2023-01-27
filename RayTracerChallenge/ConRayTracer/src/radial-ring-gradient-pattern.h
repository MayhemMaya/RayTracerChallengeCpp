#pragma once

#include "pattern.h"

class RadialRingGradientPattern : public Pattern {
public:
  RadialRingGradientPattern(const Color& a, const Color& b);
  Color pattern_at(const Point& point) override;
};