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
  float time;
  Shape* object;
  Point point;
  Vector eyev;
  Vector normalv;
  bool inside;
  Point over_point;
  Vector reflectv;
  float n1, n2;
  Point under_point;
  Computation(float time, Shape* object, const Point& point, const Vector& eyev,
                                        const Vector& normalv, const Vector& reflectv)
      : time(time), object(object), point(point), eyev(eyev),
        normalv(normalv), inside(false), reflectv(reflectv), n1(0.0f), n2(0.0f) {}
  ~Computation() {
    object = nullptr;
    delete object;
  }
};

Color lighting(const Material& material, Shape* object,
                                         const LightSource& light,
                                         const Point& point,
                                         const Vector& eyev,
                                         const Vector& normalv,
                                         bool in_shadow);
Computation prepare_computations(const Intersection& itersection, const Ray& ray);
Computation prepare_computations(const Intersection& itersection, const Ray& ray, const std::vector<Intersection>& intersections);
Color shade_hit(const World& world, const Computation& comps, int recursive_calls_remaining = utils::kRECURSION_DEPTH);
Color color_at(const World& world, const Ray& ray, int recursive_calls_remaining = utils::kRECURSION_DEPTH);
Ray ray_for_pixel(const Camera& camera, int px, int py);
Canvas render(const Camera& camera, const World& world);
bool is_shadowed(const World& world, const Point& point);
Color reflected_color(const World& world, const Computation& comps, int recursive_calls_remaining = utils::kRECURSION_DEPTH);
Color refracted_color(const World& world, const Computation& comps, int recursive_calls_remaining = utils::kRECURSION_DEPTH);
float schlick(const Computation& comps);

} // namespace Engine
