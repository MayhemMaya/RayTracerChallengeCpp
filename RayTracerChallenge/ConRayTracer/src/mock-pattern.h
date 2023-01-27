#pragma once

#include "pattern.h"
#include "colors.h"

class MockPattern : public Pattern {
public:
  MockPattern();
  Color pattern_at(const Point& point) override;
};