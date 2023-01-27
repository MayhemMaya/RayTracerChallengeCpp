#pragma once

#include "pattern.h"

class RainDropsPattern : public Pattern {
public:
  RainDropsPattern(const Color& a, const Color& b);
  Color pattern_at(const Point& point) override;
};