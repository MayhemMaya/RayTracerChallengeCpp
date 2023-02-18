#include "material.h"
#include "color.h"
#include "utils.h"

Material::Material()
  : color_(1, 1, 1),
    ambient_(0.1f),
    diffuse_(0.9f),
    specular_(0.9f),
    shininess_(200.0f),
    reflectivity_(0.0f),
    transparency_(0.0f),
    refractive_index_(1.0f),
    pattern_(nullptr) {}

Material::Material(const Color& color, float ambient, float diffuse, float specular,
                   float shininess, float reflectivity, float transparency, float refractive_index)
  : color_(color),
    ambient_(utils::clamp(ambient, 0.0f, 1.0f)),
    diffuse_(utils::clamp(diffuse, 0.0f, 1.0f)),
    specular_(utils::clamp(specular, 0.0f, 1.0f)),
    shininess_(utils::clamp(shininess, 0.0f, 1000.0f)),
    reflectivity_(utils::clamp(reflectivity, 0.0f, 1.0f)),
    transparency_(utils::clamp(transparency, 0.0f, 1.0f)),
    refractive_index_(utils::clamp(refractive_index, 1.0f, 5.0f)),
    pattern_(nullptr) {}

Material::Material(const Color& color, float ambient, float diffuse, float specular,
                   float shininess, float reflectivity, float transparency, float refractive_index,
                   Pattern* pattern)
  : color_(color),
    ambient_(utils::clamp(ambient, 0.0f, 1.0f)),
    diffuse_(utils::clamp(diffuse, 0.0f, 1.0f)),
    specular_(utils::clamp(specular, 0.0f, 1.0f)),
    shininess_(utils::clamp(shininess, 0.0f, 1000.0f)),
    reflectivity_(utils::clamp(reflectivity, 0.0f, 1.0f)),
    transparency_(utils::clamp(transparency, 0.0f, 1.0f)),
    refractive_index_(utils::clamp(refractive_index, 1.0f, 5.0f)),
    pattern_(pattern) {}

Material::Material(const Material& other)
  : color_(other.color_),
    ambient_(other.ambient_),
    diffuse_(other.diffuse_),
    specular_(other.specular_),
    shininess_(other.shininess_),
    reflectivity_(other.reflectivity_),
    transparency_(other.transparency_),
    refractive_index_(other.refractive_index_),
    pattern_(other.pattern_) {}

Material::~Material() {
  pattern_ = nullptr;
  delete pattern_;
}

Color Material::GetColor() const { return color_; }

float Material::GetAmbient() const { return ambient_; }

float Material::GetDiffuse() const { return diffuse_; }

float Material::GetSpecular() const { return specular_; }

float Material::GetShininess() const { return shininess_; }

float Material::GetReflectivity() const { return reflectivity_; }

float Material::GetTransparency() const { return transparency_; }

float Material::GetRefractiveIndex() const { return refractive_index_; }

Pattern* Material::GetPattern() const { return pattern_; }

Material& Material::SetColor(const Color& color) {
  color_ = color;
  return *this;
}

Material& Material::SetAmbient(float ambient) {
  ambient_ = utils::clamp(ambient, 0.0f, 1.0f);
  return *this;
}

Material& Material::SetDiffuse(float diffuse) {
  diffuse_ = utils::clamp(diffuse, 0.0f, 1.0f);
  return *this;
}

Material& Material::SetSpecular(float specular) {
  specular_ = utils::clamp(specular, 0.0f, 1.0f);
  return *this;
}

Material& Material::SetShininess(float shininess) {
  shininess_ = utils::clamp(shininess, 0.0f, 1000.0f);
  return *this;
}

Material& Material::SetReflectivity(float reflectivity) {
  reflectivity_ = utils::clamp(reflectivity, 0.0f, 1.0f);
  return *this;
}

Material& Material::SetTransparency(float transparency) {
  transparency_ = utils::clamp(transparency, 0.0f, 1.0f);
  return *this;
}

Material& Material::SetRefractiveIndex(float refractive_index) {
  refractive_index_ = utils::clamp(refractive_index, 1.0f, 5.0f);
  return *this;
}

Material& Material::SetPattern(Pattern* pattern) {
  pattern_ = pattern;
  return *this;
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
  utils::equal(reflectivity_, other.reflectivity_) &&
  utils::equal(transparency_, other.transparency_) &&
  utils::equal(refractive_index_, other.refractive_index_) &&
  check_patterns(pattern_, other.pattern_));
}

Material& Material::operator=(const Material& other) {
  color_ = other.color_;
  ambient_ = other.ambient_;
  diffuse_ = other.diffuse_;
  specular_ = other.specular_;
  shininess_ = other.shininess_;
  reflectivity_ = other.reflectivity_;
  transparency_ = other.transparency_;
  refractive_index_ = other.refractive_index_;
  pattern_ = other.pattern_;
  return *this;
}

std::string Material::format() const {
  std::stringstream ss;
  ss << "Color: " << color_ << "\n"
    << "Ambient: " << ambient_ << "\n"
    << "Diffuse: " << diffuse_ << "\n"
    << "Specular: " << specular_ << "\n"
    << "Shininess: " << shininess_ << "\n"
    << "Reflectivity: " << reflectivity_ << "\n"
    << "Transparency: " << transparency_ << "\n"
    << "Refractive Index: " << refractive_index_ << std::endl;
  return ss.str();
}
