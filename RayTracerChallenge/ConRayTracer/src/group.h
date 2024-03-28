#pragma once

#include "shape.h"

class Group : public Shape {
public:
  Group();
  Group(const std::string& name);
  Group(const std::string& name, const std::vector<Shape*>& children);
  Group(const std::string& name, const std::vector<Shape*>& children, const Material& material);
  Group(const std::string& name, const std::vector<Shape*>& children, const Matrix4& transform);
  Group(const std::string& name, const std::vector<Shape*>& children, const Material& material, const Matrix4& transform);
  virtual ~Group();
  std::vector<Shape*> GetChildren() const;
  void AddChild(Shape* child);
  void RemoveChild(Shape* child);
  void AddChildren(const std::vector<Shape*>& children);
  int GetChildrenCount() const;
  bool isEmpty() const;
  bool ContainsChild(Shape* other) const;
  bool ContainsChildWithName(const std::string& name) const;
  //bool operator==(const Object& object) override;
  //Group& operator=(const Object& object) override;
  std::vector<Intersection> local_intersect(const utils::RayStruct& local_ray) override;
  Vector local_normal_at(const Point& local_point, const Intersection& hit = Intersection()) const override;
  BoundingBox bounds() const override final;
  void ListDetails() const override final;
  void SetMaterial(const Material& material) override;
  void SetTransform(const Matrix4& transform) override;

private:
  std::vector<Shape*> children_;
  std::vector<Matrix4> transform_inverses_;
  BoundingBox bounds_;
  void extend_bounds(Shape* shape);
  bool intersects_bounds(const utils::RayStruct& ray);
};