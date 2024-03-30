#pragma once

#include "shape.h"

enum class Operation {
  UNION,
  INTERSECTION,
  DIFFERENCE
};

class CSG : public Shape {
public:
  CSG(const Operation& operation, Shape* left, Shape* right);
  CSG(const std::string& name, const Operation& operation, Shape* left, Shape* right);
  CSG(const std::string& name, const Operation& operation, Shape* left, Shape* right, const Matrix4& transform);
  ~CSG() override;
  Operation GetOperation() const;
  Shape* GetLeft() const;
  Shape* GetRight() const;
  void SetLeft(Shape* left);
  void SetRight(Shape* right);
  std::vector<Intersection> filter_intersections(const std::vector<Intersection>& xs) const;
  bool operator==(const Object& object) const override;
  CSG& operator=(const Object& object) override;
  std::vector<Intersection> local_intersect(const utils::RayStruct& local_ray) override;
  Vector local_normal_at(const Point& local_point, const Intersection& hit = Intersection()) const override;
  BoundingBox bounds() const override final;
  static bool intersection_allowed(Operation op, bool lhit, bool inl, bool inr);

private:
  Operation operation_;
  Shape* left_;
  Shape* right_;
};