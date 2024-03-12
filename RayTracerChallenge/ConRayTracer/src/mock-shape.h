#pragma once

#include "shape.h"

class MockShape : public Shape {
 public:
   MockShape(const std::string& name);
   bool operator==(const Object& object) override;
   MockShape& operator=(const Object& other) override;
   utils::RayStruct GetSavedRay() const;
   void SetSavedRay(const Point& origin, const Vector& direction);
   std::vector<Intersection> local_intersect(const utils::RayStruct& local_ray) override;
   Vector local_normal_at(const Point& local_point) const override;
   BoundingBox bounds() const override final;
 private:
   utils::RayStruct saved_ray_;
};
