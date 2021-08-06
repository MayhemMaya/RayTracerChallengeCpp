#pragma once

#include "object.h"
#include "color.h"
#include "material.h"
#include "point.h"
#include "vector.h"

class LightSource : public Object {
public:
  LightSource(std::string name, const Point& position, const Color& intensity);
  virtual ~LightSource() = 0;
  Color GetIntensity() const;
  static int GetCount();
  static Color lighting(const Material& material, const LightSource& light,
                        const Point& point, const Vector& eyev,
                        const Vector& normalv);
private:
  static int light_count_;
  Color intensity_;
};
