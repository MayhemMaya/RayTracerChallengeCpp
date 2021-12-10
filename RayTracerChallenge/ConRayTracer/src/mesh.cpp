#include <sstream>
#include "mesh.h"
#include "material.h"

int Mesh::mesh_count_ = 0;

Mesh::Mesh(std::string name, const ObjectType& type)
    : Object(name, type) {
  mesh_count_++;
  if (name == "sphere" || name == "mesh") {
    std::stringstream ss;
    ss << mesh_count_;
    this->SetName(this->GetName() + ss.str());
  }
}

Mesh::Mesh(std::string name, const ObjectType& type, const Matrix4& transform)
    : Object(name, type, transform) {
  mesh_count_++;
  if (name == "sphere" || name == "mesh") {
    std::stringstream ss;
    ss << mesh_count_;
    this->SetName(this->GetName() + ss.str());
  }
}

Mesh::Mesh(std::string name, const ObjectType& type, const Material& material)
    : Object(name, type) {
  mesh_count_++;
  if (name == "sphere" || name == "mesh") {
    std::stringstream ss;
    ss << mesh_count_;
    this->SetName(this->GetName() + ss.str());
  }
  this->material_ = material;
}

Mesh::Mesh(std::string name, const ObjectType& type, const Material& material,
                                                   const Matrix4& transform)
    : Object(name, type, transform) {
  mesh_count_++;
  if (name == "sphere" || name == "mesh") {
    std::stringstream ss;
    ss << mesh_count_;
    this->SetName(this->GetName() + ss.str());
  }
  this->material_ = material;
}

Mesh::~Mesh() {
  mesh_count_--;
}

void Mesh::ListDetails() const {
  std::cout << "Name: " << this->GetName() << "\n"
      << "Type: " << this->GetObjectTypeName() << "\n"
      << "Transform:\n" << this->GetTransform().format()
      << "Material:\n" << this->GetMaterial().format() << std::endl;
}

Vector Mesh::normal_at(const Point& world_point) const {
  Point object_point = this->GetTransform().inverse() * world_point;
  Vector object_normal = object_point - Point(0, 0, 0);
  Vector world_normal = this->GetTransform().inverse().transpose() * object_normal;
  world_normal(3, 0); // set the w coordinate to 0
  return world_normal.normalize();
}

Material Mesh::GetMaterial() const {
  return material_;
}
void Mesh::SetMaterial(const Material& material) {
  material_ = material;
}

int Mesh::GetCount() {
  return mesh_count_;
}

bool Mesh::operator==(const Object& object) const {
  Mesh* other = (Mesh*)&object;
  return(this->GetName() == other->GetName() &&
         this->GetTransform() == other->GetTransform() &&
         this->GetObjectType() == other->GetObjectType() && 
         this->GetMaterial() == other->GetMaterial());
}

Mesh& Mesh::operator=(const Object& object) {
  Mesh* other = (Mesh*)&object;
  this->SetName(other->GetName());
  this->SetObjectType(other->GetObjectType());
  this->SetTransform(other->GetTransform());
  material_ = other->GetMaterial();
  return *this;
}
