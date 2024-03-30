#include <sstream>
#include "shape.h"
#include "material.h"
#include <stdexcept>


Shape::Shape(const std::string& name, const ObjectType& type)
    : Object(name, type), material_(Material()), can_out_out_of_shadow_(false) {}

Shape::Shape(const std::string& name, const ObjectType& type, const Matrix4& transform)
    : Object(name, type, transform), material_(Material()), can_out_out_of_shadow_(false) {}

Shape::Shape(const std::string& name, const ObjectType& type, const Material& material)
    : Object(name, type), material_(material), can_out_out_of_shadow_(false) {}

Shape::Shape(const std::string& name, const ObjectType& type, const Material& material,
                                                   const Matrix4& transform)
    : Object(name, type, transform), material_(material), can_out_out_of_shadow_(false) {}

Shape::~Shape() {}

void Shape::ListDetails() const {
  std::string parent_name = parent_ == nullptr ? "None" : parent_->GetName();
  std::cout << "Name: " << name_ << "\n"
      << "Type: " << this->GetObjectTypeName() << "\n"
      << "ID: " << this->GetID() << "\n"
      << "Transform:\n" << transform_.format()
      << "Parent: " << parent_name << "\n\n";
}

Vector Shape::normal_at(const Point& point, const Intersection& hit) const {
  Point local_point = Shape::world_to_object(this, point);
  Vector local_normal = this->local_normal_at(local_point, hit);
  return Shape::normal_to_world(this, local_normal);
}

Material& Shape::GetMaterial() {
  return material_;
}
void Shape::SetMaterial(const Material& material) {
  material_ = material;
}

bool Shape::GetCanOptOutOfShadow() const {
  return can_out_out_of_shadow_;
}

void Shape::SetCanOptOutOfShadow(bool opt_out) {
  can_out_out_of_shadow_ = opt_out;
}

bool Shape::operator==(const Object& object) const {
  Shape* other = (Shape*)&object;
  return(name_ == other->GetName() &&
         transform_ == other->GetTransform() &&
         type_ == other->GetObjectType() && 
         id_ == other->GetID() && 
         material_ == other->GetMaterial() &&
         parent_ == other->GetParent());
}

Shape& Shape::operator=(const Object& object) {
  Shape* other = (Shape*)&object;
  name_ = other->GetName();
  type_ = other->GetObjectType();
  transform_ = other->GetTransform();
  material_ = other->GetMaterial();
  parent_ = other->GetParent();
  return *this;
}

Vector Shape::normal_to_world(const Object* shape, Vector normal) {
  normal = shape->GetCachedTransformInverse().transpose() * normal;
  normal(3, 0); // set w coordinate to 0
  normal = normal.normalize();

  if (shape->HasParent()) {
    normal = Shape::normal_to_world(shape->GetParent(), normal);
  }

  return normal;
}
