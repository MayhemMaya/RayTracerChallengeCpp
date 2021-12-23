#include "sphere.h"
#include "vector.h"
#include "point.h"

Sphere::Sphere() : Mesh("sphere", ObjectType::kSphere) {}

Sphere::Sphere(const std::string& name) : Mesh(name, ObjectType::kSphere) {}

Sphere::Sphere(const Material& material)
    : Mesh("sphere", ObjectType::kSphere, material) {}

Sphere::Sphere(const Matrix4& transform)
    : Mesh("sphere", ObjectType::kSphere, transform) {}

Sphere::Sphere(const std::string& name, const Material& material)
    : Mesh(name, ObjectType::kSphere, material) {}

Sphere::Sphere(const std::string& name, const Matrix4& transform)
    : Mesh(name, ObjectType::kSphere, transform) {}

Sphere::Sphere(const Material& material, const Matrix4& transform)
    : Mesh("sphere", ObjectType::kSphere, material, transform) {}

Sphere::Sphere(const std::string& name, const Material& material, const Matrix4& transform)
    : Mesh(name, ObjectType::kSphere, material, transform) {}

bool Sphere::operator==(const Object& object) const {
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
