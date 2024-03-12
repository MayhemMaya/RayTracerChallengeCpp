#pragma once

#include <iostream>
#include "color.h"
#include "utils.h"
#include "pattern.h"

class Material {
 public:
   Material();
   Material(const Color& color, float ambient, float diffuse, float specular,
            float shininess, float reflectivity, float transparency, float refractive_index);
   Material(const Color& color, float ambient, float diffuse, float specular,
            float shininess, float reflectivity, float transparency, float refractive_index,
            Pattern* pattern);
   Material(const Material& other);
   ~Material();
   Color GetColor() const;
   float GetAmbient() const;
   float GetDiffuse() const;
   float GetSpecular() const;
   float GetShininess() const;
   float GetReflectivity() const;
   float GetTransparency() const;
   float GetRefractiveIndex() const;
   Pattern* GetPattern() const;

   // by having the Set functions return a material reference we allow for chained single line set functions
   // E.g: Material().SetColor(...).SetTransparency(...).SetDiffuse(...);
   Material& SetColor(const Color& color);
   Material& SetAmbient(float ambient);
   Material& SetDiffuse(float diffuse);
   Material& SetSpecular(float specular);
   Material& SetShininess(float shininess);
   Material& SetReflectivity(float reflectivity);
   Material& SetTransparency(float transparency);
   Material& SetRefractiveIndex(float refractive_index);
   Material& SetPattern(Pattern* pattern);
   bool operator==(const Material& other) const;
   Material& operator=(const Material& other);
 private:
  Color color_;
  float ambient_;
  float diffuse_;
  float specular_;
  float shininess_;
  float reflectivity_;
  float transparency_;
  float refractive_index_;
  Pattern* pattern_;
};
