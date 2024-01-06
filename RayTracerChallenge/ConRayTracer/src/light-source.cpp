#include <sstream>
#include <cmath>
#include "light-source.h"
#include "color.h"
#include "vector.h"
#include "utils.h"

int LightSource::light_count_ = 0;

LightSource::LightSource(const std::string& name, const ObjectType& type,
                                           const Point& position,
                                           const Color& intensity)
    : Object(name, type, position), intensity_(intensity) {
  light_count_++;
}

LightSource::~LightSource() {
  light_count_--;
}

/*
void LightSource::ListDetails() const {
  std::cout << "Name: " << this->GetName() << "\n"
      << "Type: " << this->GetObjectTypeName() << "\n"
      << "Transform:\n" << this->GetTransform().format()
      << "Intensity: " << intensity_ << std::endl;
}*/

Color LightSource::GetIntensity() const {
  return intensity_;
}

void LightSource::SetIntensity(const Color& intensity) {
  intensity_ = intensity;
}

int LightSource::GetCount() {
  return light_count_;
}

bool LightSource::operator==(const Object& object) {
  LightSource* other = (LightSource*)&object;
  return(this->GetName() == other->GetName() &&
    this->GetTransform() == other->GetTransform() &&
    this->GetObjectType() == other->GetObjectType() &&
    this->GetIntensity() == other->GetIntensity());
}

/*
LightSource& LightSource::operator=(const Object& object) {
  LightSource* other = (LightSource*)&object;
  this->SetName(other->GetName());
  this->SetObjectType(other->GetObjectType());
  this->SetTransform(other->GetTransform());
  intensity_ = other->GetIntensity();
  return *this;
}*/