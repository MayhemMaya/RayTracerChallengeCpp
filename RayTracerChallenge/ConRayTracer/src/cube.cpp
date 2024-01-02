#include "cube.h"
#include <algorithm>

Cube::Cube() : Shape("cube", ObjectType::kCube) {}

Cube::Cube(const std::string& name)
  : Shape(name, ObjectType::kCube) {}

Cube::Cube(const Material& material)
  : Shape("cube", ObjectType::kCube, material) {}

Cube::Cube(const Matrix4& transform)
  : Shape("cube", ObjectType::kCube, transform) {}

Cube::Cube(const std::string& name, const Material& material)
  : Shape(name, ObjectType::kCube, material) {}

Cube::Cube(const std::string& name, const Matrix4& transform)
  : Shape(name, ObjectType::kCube, transform) {}

Cube::Cube(const Material& material, const Matrix4& transform)
  : Shape("cube", ObjectType::kCube, material, transform) {}

Cube::Cube(const std::string& name, const Material& material, const Matrix4& transform)
  : Shape(name, ObjectType::kCube, material, transform) {}

bool Cube::operator==(const Object& object) {
  Cube* other = (Cube*)&object;
  return(this->GetName() == other->GetName() &&
    this->GetTransform() == other->GetTransform() &&
    this->GetObjectType() == other->GetObjectType() &&
    this->GetMaterial() == other->GetMaterial());
}

Cube& Cube::operator=(const Object& object) {
  Cube* other = (Cube*)&object;
  this->SetName(other->GetName());
  this->SetObjectType(other->GetObjectType());
  this->SetTransform(other->GetTransform());
  this->SetMaterial(other->GetMaterial());
  return *this;
}

TimeValuePair check_axis(float axis_origin, float axis_direction) {
  const auto tmin_numerator = (-1 - axis_origin);
  const auto tmax_numerator = (1 - axis_origin);

  TimeValuePair pair;

  if (abs(axis_direction) >= utils::kEPSILON) {
    pair.tmin = tmin_numerator / axis_direction;
    pair.tmax = tmax_numerator / axis_direction;
  }
  else {
    pair.tmin = tmin_numerator * utils::kINFINITY;
    pair.tmax = tmax_numerator * utils::kINFINITY;
  }

  if (pair.tmin > pair.tmax) utils::swap(pair.tmin, pair.tmax);

  return pair;
}

std::vector<Intersection> Cube::local_intersect(const utils::RayStruct& local_ray) {
  TimeValuePair x = check_axis(local_ray.origin[0], local_ray.direction[0]);
  TimeValuePair y = check_axis(local_ray.origin[1], local_ray.direction[1]);
  TimeValuePair z = check_axis(local_ray.origin[2], local_ray.direction[2]);

  const auto tmin = std::max({ x.tmin, y.tmin, z.tmin });
  const auto tmax = std::min({ x.tmax, y.tmax, z.tmax });

  if (tmin > tmax || tmax < 0) return {};

  return { Intersection(tmin, this), Intersection(tmax, this) };
}

Vector Cube::local_normal_at(const Point& local_point) const {
  const auto maxc = std::max({ abs(local_point[0]), abs(local_point[1]), abs(local_point[2]) });

  if (maxc == abs(local_point[0])) {
    return Vector(local_point[0], 0, 0);
  }
  else if (maxc == abs(local_point[1])) {
    return Vector(0, local_point[1], 0);
  }
  return Vector(0, 0, local_point[2]);
}