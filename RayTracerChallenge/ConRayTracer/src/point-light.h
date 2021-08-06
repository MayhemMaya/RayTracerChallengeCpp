#pragma once

#include "light-source.h"
#include "point.h"
#include "color.h"

class PointLight : public LightSource {
 public:
   PointLight(const Point& position, const Color& intensity);
};