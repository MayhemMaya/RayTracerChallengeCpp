#pragma once

#include "pattern.h"

class BlendedPattern : public Pattern {
public:
  BlendedPattern(Pattern* a, Pattern* b);
  Color pattern_at(const Point& point) override;
};