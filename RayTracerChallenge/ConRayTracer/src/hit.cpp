#include <vector>
#include "hit.h"
#include "intersection.h"

Hit Hit::hit(std::vector<Intersection> intersections) {
  Hit hit;
  for (Intersection i : intersections) {
    if (i.GetTime() > 0) {
      hit.i = i;
      hit.result = HitResult::HIT;
      break;
    }
  }
  return hit;
}