#include "point-light.h"
#include "point.h"
#include "color.h"

PointLight::PointLight(const Point& position, const Color& intensity)
    : LightSource("pointlight", ObjectType::kPointLight, position, intensity) {}

PointLight::PointLight(const std::string& name, const Point& position, const Color& intensity)
    : LightSource(name, ObjectType::kPointLight, position, intensity) {}

bool PointLight::operator==(const Object& object) const {
  PointLight* other = (PointLight*)&object;
  return(this->GetName() == other->GetName() &&
    this->GetTransform() == other->GetTransform() &&
    this->GetObjectType() == other->GetObjectType() &&
    this->GetIntensity() == other->GetIntensity());
}

PointLight& PointLight::operator=(const Object& object) {
  PointLight* other = (PointLight*)&object;
  this->SetName(other->GetName());
  this->SetObjectType(other->GetObjectType());
  this->SetTransform(other->GetTransform());
  this->SetIntensity(other->GetIntensity());
  return *this;
}
