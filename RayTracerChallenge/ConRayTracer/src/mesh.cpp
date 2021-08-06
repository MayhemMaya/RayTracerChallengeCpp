#include <sstream>
#include "mesh.h"
#include "material.h"

int Mesh::mesh_count_ = 0;

Mesh::Mesh(std::string name) : Object(name) {
  mesh_count_++;
  if (name == "sphere") {
    std::stringstream ss;
    ss << mesh_count_;
    this->SetName(this->GetName() + ss.str());
  }
}

Mesh::~Mesh() {
  mesh_count_--;
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
