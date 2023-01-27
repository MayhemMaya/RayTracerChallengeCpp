#include "material.h"
#include "color.h"
#include "utils.h"

Material::Material()
    : color_(1, 1, 1),
      ambient_(0.1f),
      diffuse_(0.9f),
      specular_(0.9f),
      shininess_(200.0f),
      pattern_(nullptr) {}

Material::Material(const Color& color, float ambient, float diffuse,
                   float specular, float shininess, Pattern* pattern)
    : color_(color),
      ambient_(utils::clamp(ambient, 0.0f, 1.0f)),
      diffuse_(utils::clamp(diffuse, 0.0f, 1.0f)),
      specular_(utils::clamp(specular, 0.0f, 1.0f)),
      shininess_(utils::clamp(shininess, 0.0f, 200.0f)),
      pattern_(pattern) {}

Material::~Material() {
  pattern_ = nullptr;
  delete pattern_;
}

Color Material::GetColor() const { return color_; }

float Material::GetAmbient() const { return ambient_; }

float Material::GetDiffuse() const { return diffuse_; }

float Material::GetSpecular() const { return specular_; }

float Material::GetShininess() const { return shininess_; }

Pattern* Material::GetPattern() const {
  return pattern_;
}

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

void Material::SetPattern(Pattern* pattern) {
  pattern_ = pattern;
}

bool check_patterns(Pattern* p1, Pattern* p2) {
  if (p1 == nullptr && p2 == nullptr) return true;
  if (p1 != nullptr && p2 != nullptr) {
    if ((*p1) == (*p2)) {
      return true;
    }
  }
  return false;
}

bool Material::operator==(const Material& other) const {
  return(color_ == other.color_ &&
    utils::equal(ambient_, other.ambient_) &&
    utils::equal(diffuse_, other.diffuse_) &&
    utils::equal(specular_, other.specular_) &&
    utils::equal(shininess_, other.shininess_) &&
    check_patterns(pattern_, other.pattern_));
}

Material& Material::operator=(const Material& other) {
  color_ = other.color_;
  ambient_ = other.ambient_;
  diffuse_ = other.diffuse_;
  specular_ = other.specular_;
  shininess_ = other.shininess_;
  pattern_ = other.pattern_;
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
