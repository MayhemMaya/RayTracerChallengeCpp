#pragma once

#include "utils.h"
#include "color.h"
#include "material.h"
#include "light-source.h"
#include "point.h"
#include "vector.h"
#include "shape.h"
#include "intersection.h"
#include "ray.h"
#include "world.h"
#include "hit.h"
#include "matrix4.h"
#include "camera.h"
#include "canvas.h"

namespace Engine {

struct Computation {
  float time_;
  Shape* object_;
  Point point_;
  Vector eyev_;
  Vector normalv_;
  bool inside_;
  Point over_point_;
  Computation(float time, Shape* object, const Point& point, const Vector& eyev,
                                        const Vector& normalv)
      : time_(time), object_(object), point_(point), eyev_(eyev),
        normalv_(normalv), inside_(false) {}
  Computation(float time, Shape* object, const Point& point, const Vector& eyev,
    const Vector& normalv, bool inside, const Point& over_point)
    : time_(time), object_(object), point_(point), eyev_(eyev),
    normalv_(normalv), inside_(inside), over_point_(over_point) {}
  ~Computation() {
    object_ = nullptr;
    delete object_;
  }
};

Color lighting(const Material& material, Shape* object,
                                         const LightSource& light,
                                         const Point& point,
                                         const Vector& eyev,
                                         const Vector& normalv,
                                         bool in_shadow);
Computation prepare_computations(const Intersection& itersection, const Ray& ray);
Color shade_hit(const World& world, const Computation& comp);
Color color_at(const World& world, const Ray& ray);
Ray ray_for_pixel(const Camera& camera, int px, int py);
Canvas render(const Camera& camera, const World& world);
bool is_shadowed(const World& world, const Point& point);

} // namespace Engine
