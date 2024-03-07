#pragma once

#include "shape.h"

struct GroupChild {
  Shape* child;
  Matrix4 transform;
};

class Group : public Shape {
public:
  Group(const std::string& name);
  Group(const std::string& name, const std::vector<Shape*>& children);
  Group(const std::string& name, const std::vector<Shape*>& children, const Material& material);
  Group(const std::string& name, const std::vector<Shape*>& children, const Matrix4& transform);
  Group(const std::string& name, const std::vector<Shape*>& children, const Material& material, const Matrix4& transform);
  virtual ~Group();
  std::vector<GroupChild> GetChildren() const;
  void AddChild(Shape* child);
  void RemoveChild(Shape* child);
  void AddChildren(const std::vector<Shape*>& children);
  int GetChildrenCount() const;
  bool isEmpty() const;
  bool ContainsChild(Shape* other) const;
  /*bool operator==(const Object& object) override;
  Group& operator=(const Object& object) override;*/
  std::vector<Intersection> local_intersect(const utils::RayStruct& local_ray) override;
  Vector local_normal_at(const Point& local_point) const override;

private:
  std::vector<GroupChild> children_;
};