#include "material.h"
#include "color.h"
#include "utils.h"

Material::Material()
    : color_(1, 1, 1),
      ambient_(0.1f),
      diffuse_(0.9f),
      specular_(0.9f),
      shininess_(200.0f) {}

Material::Material(const Color& color, float ambient, float diffuse,
                   float specular, float shininess)
    : color_(color),
      ambient_(utils::clamp(ambient, 0.0f, 1.0f)),
      diffuse_(utils::clamp(diffuse, 0.0f, 1.0f)),
      specular_(utils::clamp(specular, 0.0f, 1.0f)),
      shininess_(utils::clamp(shininess, 0.0f, 200.0f)) {}

std::ostream& operator<<(std::ostream& os, const Material& obj) {
  os << "Color: " << obj.color_ << "\n"
    << "Ambient: " << obj.ambient_ << "\n"
    << "Diffuse: " << obj.diffuse_ << "\n"
    << "Specular: " << obj.specular_ << "\n"
    << "Shininess: " << obj.shininess_;
  return os;
}

Color Material::GetColor() const { return color_; }

float Material::GetAmbient() const { return ambient_; }

float Material::GetDiffuse() const { return diffuse_; }

float Material::GetSpecular() const { return specular_; }

float Material::GetShininess() const { return shininess_; }

void Material::SetColor(const Color& color) {
  color_ = color;
}

void Material::SetAmbient(float ambient) {
  ambient_ = utils::clamp(ambient, 0.0f, 1.0f);
}

void Material::SetDiffuse(float diffuse) {
  diffuse_ = utils::clamp(diffuse, 0.0f, 1.0f);
}

void Material::SetSpecular(float specular) {
  specular_ = utils::clamp(specular, 0.0f, 1.0f);
}

void Material::SetShininess(float shininess) {
  shininess_ = utils::clamp(shininess, 0.0f, 200.0f);
}

bool Material::operator==(const Material& other) const {
  return(color_ == other.color_ &&
         utils::equal(ambient_, other.ambient_) &&
         utils::equal(diffuse_, other.diffuse_) &&
         utils::equal(specular_, other.specular_) &&
         utils::equal(shininess_, other.shininess_));
}

Material& Material::operator=(const Material& other) {
  color_ = other.color_;
  ambient_ = other.ambient_;
  diffuse_ = other.diffuse_;
  specular_ = other.specular_;
  shininess_ = other.shininess_;
  return *this;
}

std::string Material::format() const {
  std::stringstream ss;
  ss << "Color: " << color_ << "\n"
    << "Ambient: " << ambient_ << "\n"
    << "Diffuse: " << diffuse_ << "\n"
    << "Specular: " << specular_ << "\n"
    << "Shininess: " << shininess_ << std::endl;
  return ss.str();
}
