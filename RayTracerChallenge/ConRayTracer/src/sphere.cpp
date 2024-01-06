#include "sphere.h"
#include "vector.h"
#include "point.h"

Sphere::Sphere(const std::string& name)
    : Shape(name, ObjectType::kSphere) {
}

Sphere::Sphere(const std::string& name, const Material& material)
    : Shape(name, ObjectType::kSphere, material) {
}

Sphere::Sphere(const std::string& name, const Matrix4& transform)
    : Shape(name, ObjectType::kSphere, transform) {
}

Sphere::Sphere(const std::string& name, const Material& material, const Matrix4& transform)
    : Shape(name, ObjectType::kSphere, material, transform) {
}

bool Sphere::operator==(const Object& object) {
  Sphere* other = (Sphere*)&object;
  return(this->GetName() == other->GetName() &&
    this->GetTransform() == other->GetTransform() &&
    this->GetObjectType() == other->GetObjectType() &&
    this->GetMaterial() == other->GetMaterial());
}

Sphere& Sphere::operator=(const Object& object) {
  Sphere* other = (Sphere*)&object;
  this->SetName(other->GetName());
  this->SetObjectType(other->GetObjectType());
  this->SetTransform(other->GetTransform());
  this->SetMaterial(other->GetMaterial());
  return *this;
}

std::vector<Intersection> Sphere::local_intersect(const utils::RayStruct& local_ray) {
  Vector sphere_to_ray = local_ray.origin - Point(0, 0, 0);

  float a = local_ray.direction.dot(local_ray.direction);
  float b = 2.0f * local_ray.direction.dot(sphere_to_ray);
  float c = sphere_to_ray.dot(sphere_to_ray) - 1;
  float discriminant = pow(b, 2) - 4 * a * c;
  if (discriminant < 0) return {};
  float t1 = (-b - sqrt(discriminant)) / (2 * a);
  float t2 = (-b + sqrt(discriminant)) / (2 * a);

  return { Intersection(t1, this), Intersection(t2, this) };
}

Vector Sphere::local_normal_at(const Point& local_point) const {
  Vector local_normal = local_point - Point(0, 0, 0);
  return local_normal.normalize();
}

Sphere Sphere::glass_sphere(const std::string& name) {
  Sphere s = Sphere(name);
  s.GetMaterial().SetTransparency(1.0f).SetRefractiveIndex(1.5f);
  return s;
}

Sphere Sphere::glass_sphere(const std::string& name, const Matrix4& transform) {
  Sphere s = Sphere(name, transform);
  s.GetMaterial().SetTransparency(1.0f).SetRefractiveIndex(1.5f);
  return s;
}
