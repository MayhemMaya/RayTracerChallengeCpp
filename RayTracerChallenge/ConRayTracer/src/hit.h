#pragma once

#include <vector>
#include "intersection.h"

enum class HitResult {
  HIT,
  NO_HIT
};

struct Hit {
  Intersection i;
  HitResult result = HitResult::NO_HIT;
  static Hit hit(std::vector<Intersection> intersections);
};