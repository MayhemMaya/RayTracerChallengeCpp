#pragma once

#include "utils.h"
#include "color.h"
#include "material.h"
#include "light-source.h"
#include "point.h"
#include "vector.h"
#include "mesh.h"
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
  Mesh object_;
  Point point_;
  Vector eyev_;
  Vector normalv_;
  bool inside_;
  Computation() : Computation(0, Mesh("mesh", ObjectType::kUnknown), Point(0, 0, 0),
    Vector(0, 0, 0), Vector(0, 0, 0), false) {}
  Computation(float time, Mesh object, Point point, Vector eyev,
                                        Vector normalv, bool inside)
      : time_(time), object_(object), point_(point), eyev_(eyev),
        normalv_(normalv), inside_(inside) {}
};

Color lighting(const Material& material, const LightSource& light,
                                         const Point& point,
                                         const Vector& eyev,
                                         const Vector& normalv);
Computation prepare_computations(const Intersection& itersection, const Ray& ray);
Color shade_hit(const World& world, const Computation& comp);
Color color_at(const World& world, const Ray& ray);
Ray ray_for_pixel(const Camera& camera, int px, int py);
Canvas render(const Camera& camera, const World& world);

} // namespace Engine
