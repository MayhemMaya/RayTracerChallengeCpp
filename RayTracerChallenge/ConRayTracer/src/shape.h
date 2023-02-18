#pragma once

#include "object.h"
#include "material.h"
#include "vector.h"
#include "point.h"
#include "intersection.h"

// Previously known as Mesh
class Shape : public Object {
 public:
  Shape(const std::string& name, const ObjectType& type);
  Shape(const std::string& name, const ObjectType& type, const Matrix4& transform);
  Shape(const std::string& name, const ObjectType& type, const Material& material);
  Shape(const std::string& name, const ObjectType& type, const Material& material,
                                                         const Matrix4& transform);
  virtual ~Shape() = 0;
  void ListDetails() override;
  Vector normal_at(const Point& point) const;
  Material& GetMaterial();
  void SetMaterial(const Material& material);
  static int GetCount();
  bool operator==(const Object& object) override;
  Shape& operator=(const Object& other) override;
  virtual std::vector<Intersection> local_intersect(const utils::RayStruct& local_ray) = 0;
  virtual Vector local_normal_at(const Point& local_point) const = 0;

 private:
  static int shape_count_;
  Material material_;
};
