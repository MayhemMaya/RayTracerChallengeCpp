#pragma once

#include "object.h"
#include "material.h"
#include "vector.h"
#include "point.h"
#include "intersection.h"
#include "bounding-box.h"

// Previously known as Mesh
class Shape : public Object {
 public:
  Shape(const std::string& name, const ObjectType& type);
  Shape(const std::string& name, const ObjectType& type, const Matrix4& transform);
  Shape(const std::string& name, const ObjectType& type, const Material& material);
  Shape(const std::string& name, const ObjectType& type, const Material& material,
                                                         const Matrix4& transform);
  virtual ~Shape() override = 0;
  void ListDetails() const override;
  Vector normal_at(const Point& point, const Intersection& hit = Intersection()) const;
  Material& GetMaterial();
  virtual void SetMaterial(const Material& material);
  bool GetCanOptOutOfShadow() const;
  void SetCanOptOutOfShadow(bool opt_out);
  bool operator==(const Object& object) const override;
  Shape& operator=(const Object& other) override;
  virtual std::vector<Intersection> local_intersect(const utils::RayStruct& local_ray) = 0;
  virtual Vector local_normal_at(const Point& local_point, const Intersection& hit = Intersection()) const = 0;
  static Vector normal_to_world(const Object* shape, Vector normal);
  virtual BoundingBox bounds() const = 0;
 protected:
  Material material_;
  bool can_out_out_of_shadow_;
};
