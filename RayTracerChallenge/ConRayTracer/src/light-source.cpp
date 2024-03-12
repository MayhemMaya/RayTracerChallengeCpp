#include <sstream>
#include <cmath>
#include "light-source.h"
#include "color.h"
#include "vector.h"
#include "utils.h"


LightSource::LightSource(const std::string& name, const ObjectType& type,
                                           const Point& position,
                                           const Color& intensity)
    : Object(name, type, position), intensity_(intensity) {}

LightSource::~LightSource() {}


void LightSource::ListDetails() const {
  std::string parent_name = parent_ == nullptr ? "None" : parent_->GetName();
  std::cout << "Name: " << this->GetName() << "\n"
      << "Type: " << this->GetObjectTypeName() << "\n"
      << "ID: " << this->GetID() << "\n"
      << "Transform:\n" << this->GetTransform().format()
      << "Parent: " << parent_name << "\n"
      << "Intensity: " << intensity_ << "\n";
}

Color LightSource::GetIntensity() const {
  return intensity_;
}

void LightSource::SetIntensity(const Color& intensity) {
  intensity_ = intensity;
}

bool LightSource::operator==(const Object& object) const {
  LightSource* other = (LightSource*)&object;
  return(this->GetName() == other->GetName() &&
    this->GetTransform() == other->GetTransform() &&
    this->GetObjectType() == other->GetObjectType() &&
    this->GetParent() == other->GetParent() &&
    this->GetID() == other->GetID() &&
    this->GetIntensity() == other->GetIntensity());
}

LightSource& LightSource::operator=(const Object& object) {
  LightSource* other = (LightSource*)&object;
  name_ = other->GetName();
  type_ = other->GetObjectType();
  transform_ = other->GetTransform();
  parent_ = other->GetParent();
  intensity_ = other->GetIntensity();
  return *this;
}