#pragma once

#include "shape.h"

class Sphere : public Shape {
 public:
   Sphere();
   Sphere(const std::string& name);
   Sphere(const std::string& name, const Material& material);
   Sphere(const std::string& name, const Matrix4& transform);
   Sphere(const std::string& name, const Material& material, const Matrix4& transform);
   bool operator==(const Object& object) const override;
   Sphere& operator=(const Object& other) override;
   std::vector<Intersection> local_intersect(const utils::RayStruct& local_ray) override;
   Vector local_normal_at(const Point& local_point, const Intersection& hit = Intersection()) const override;
   static Sphere glass_sphere(const std::string& name);
   static Sphere glass_sphere(const std::string& name, const Matrix4& transform);
   BoundingBox bounds() const override final;
};
