#include <sstream>
#include <cmath>
#include "light-source.h"
#include "color.h"
#include "material.h"
#include "vector.h"
#include "utils.h"

int LightSource::light_count_ = 0;

LightSource::LightSource(std::string name, const Point& position,
                         const Color& intensity) : Object(name, position),
                                                   intensity_(intensity) {
  light_count_++;
  if (name == "pointlight") {
    std::stringstream ss;
    ss << light_count_;
    this->SetName(this->GetName() + ss.str());
  }
}

Color LightSource::GetIntensity() const {
  return intensity_;
}

LightSource::~LightSource() {
  light_count_--;
}

int LightSource::GetCount() {
  return light_count_;
}

Color LightSource::lighting(const Material& material, const LightSource& light,
                            const Point& point, const Vector& eyev,
                            const Vector& normalv) {
  // set diffuse and specular to black to start
  Color diffuse(0, 0, 0);
  Color specular(0, 0, 0);

  // combine the surface color with the light's color/intensity
  Color effective_color = material.GetColor() * light.GetIntensity();

  // find the direction to the light source
  Vector lightv = (light.GetPosition() - point).normalize();

  // compute the ambient contribution
  Color ambient = effective_color * material.GetAmbient();

  // light_dot_normal represents the cosine of the angle between the
  // light vector and the normal vector. A negative number means the
  // light is on the other side of the surface.
  float light_dot_normal = utils::dot(lightv, normalv);
  if (light_dot_normal < 0) {
    diffuse = Color(0, 0, 0); // black
    specular = Color(0, 0, 0); // black
  }
  else {
    // compute the diffuse contribution
    diffuse = effective_color * material.GetDiffuse() * light_dot_normal;

    // reflect_dot_eye represents the cosine of the angle between the
    // reflection vectorand the eye vector.A negative number means the
    // light reflects away from the eye.
    Vector reflectv = -lightv.reflect(normalv);
    float reflect_dot_eye = utils::dot(reflectv, eyev);

    if (reflect_dot_eye <= 0) {
      specular = Color(0, 0, 0); // black
    }
    else {
      // compute the specular contribution
      float factor = pow(reflect_dot_eye, material.GetShininess());
      specular = light.GetIntensity() * material.GetSpecular() * factor;
    }
  }
  return(ambient + diffuse + specular).round(4);
}