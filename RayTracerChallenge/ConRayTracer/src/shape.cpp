#include <sstream>
#include "shape.h"
#include "material.h"

int Shape::shape_count_ = 0;

Shape::Shape(const std::string& name, const ObjectType& type)
    : Object(name, type) {
  shape_count_++;
}

Shape::Shape(const std::string& name, const ObjectType& type, const Matrix4& transform)
    : Object(name, type, transform) {
  shape_count_++;
}

Shape::Shape(const std::string& name, const ObjectType& type, const Material& material)
    : Object(name, type) {
  shape_count_++;
  this->material_ = material;
}

Shape::Shape(const std::string& name, const ObjectType& type, const Material& material,
                                                   const Matrix4& transform)
    : Object(name, type, transform) {
  shape_count_++;
  this->material_ = material;
}

Shape::~Shape() {
  shape_count_--;
}

void Shape::ListDetails() {
  std::cout << "Name: " << this->GetName() << "\n"
      << "Type: " << this->GetObjectTypeName() << "\n"
      << "Transform:\n" << this->GetTransform().format()
      << "Material:\n" << this->GetMaterial().format() << std::endl;
}

Vector Shape::normal_at(const Point& point) const {
  Matrix4 shape_inverse = this->GetSavedTransformInverse();
  Point local_point = shape_inverse * point;
  Vector local_normal = this->local_normal_at(local_point);
  Vector world_normal = shape_inverse.transpose() * local_normal;
  world_normal(3, 0); // set the w coordinate to 0
  return world_normal.normalize();
}

Material& Shape::GetMaterial() {
  return material_;
}
void Shape::SetMaterial(const Material& material) {
  material_ = material;
}

int Shape::GetCount() {
  return shape_count_;
}

bool Shape::operator==(const Object& object) {
  Shape* other = (Shape*)&object;
  return(this->GetName() == other->GetName() &&
         this->GetTransform() == other->GetTransform() &&
         this->GetObjectType() == other->GetObjectType() && 
         this->GetMaterial() == other->GetMaterial());
}

Shape& Shape::operator=(const Object& object) {
  Shape* other = (Shape*)&object;
  this->SetName(other->GetName());
  this->SetObjectType(other->GetObjectType());
  this->SetTransform(other->GetTransform());
  material_ = other->GetMaterial();
  return *this;
}
