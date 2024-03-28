#include "cube.h"
#include "utils.h"
#include <algorithm>

Cube::Cube()
  : Shape("cube", ObjectType::kCube) {}

Cube::Cube(const std::string& name)
  : Shape(name, ObjectType::kCube) {}

Cube::Cube(const std::string& name, const Material& material)
  : Shape(name, ObjectType::kCube, material) {}

Cube::Cube(const std::string& name, const Matrix4& transform)
  : Shape(name, ObjectType::kCube, transform) {}

Cube::Cube(const std::string& name, const Material& material, const Matrix4& transform)
  : Shape(name, ObjectType::kCube, material, transform) {}

bool Cube::operator==(const Object& object) const {
  Cube* other = (Cube*)&object;
  return(name_ == other->GetName() &&
    transform_ == other->GetTransform() &&
    type_ == other->GetObjectType() &&
    parent_ == other->GetParent() &&
    id_ == other->GetID() &&
    material_ == other->GetMaterial());
}

Cube& Cube::operator=(const Object& object) {
  Cube* other = (Cube*)&object;
  name_ = other->GetName();
  type_ = other->GetObjectType();
  transform_ = other->GetTransform();
  material_ = other->GetMaterial();
  parent_ = other->GetParent();
  return *this;
}

std::vector<Intersection> Cube::local_intersect(const utils::RayStruct& local_ray) {
  // using structured bindings here now.
  const auto [x_tmin, x_tmax] = utils::check_axis(local_ray.origin[0], local_ray.direction[0], -1, 1);
  const auto [y_tmin, y_tmax] = utils::check_axis(local_ray.origin[1], local_ray.direction[1], -1, 1);
  const auto [z_tmin, z_tmax] = utils::check_axis(local_ray.origin[2], local_ray.direction[2], -1, 1);

  const auto tmin = std::max({ x_tmin, y_tmin, z_tmin });
  const auto tmax = std::min({ x_tmax, y_tmax, z_tmax });

  if (tmin > tmax || tmax < 0) return {};

  return { Intersection(tmin, this), Intersection(tmax, this) };
}

Vector Cube::local_normal_at(const Point& local_point, const Intersection& hit) const {
  const auto maxc = std::max({ abs(local_point[0]), abs(local_point[1]), abs(local_point[2]) });

  if (maxc == abs(local_point[0])) {
    return Vector(local_point[0], 0, 0);
  }
  else if (maxc == abs(local_point[1])) {
    return Vector(0, local_point[1], 0);
  }
  return Vector(0, 0, local_point[2]);
}

BoundingBox Cube::bounds() const {
  return BoundingBox(Point(-1, -1, -1), Point(1, 1, 1));
}