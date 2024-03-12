#pragma once

#include "light-source.h"
#include "point.h"
#include "color.h"

class PointLight : public LightSource {
 public:
   PointLight(const std::string& name, const Point& position, const Color& intensity);
   bool operator==(const Object& object) const override;
   PointLight& operator=(const Object& other) override;
};