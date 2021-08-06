#pragma once

#include "color.h"
#include "utils.h"

class Material {
 public:
   Material();
   Material(const Color& color, float ambient, float diffuse,
            float specular, float shininess);
   Color GetColor() const;
   float GetAmbient() const;
   float GetDiffuse() const;
   float GetSpecular() const;
   float GetShininess() const;

   void SetColor(const Color& color);
   void SetAmbient(float ambient);
   void SetDiffuse(float diffuse);
   void SetSpecular(float specular);
   void SetShininess(float shininess);
   bool operator==(const Material& other) const;
 private:
  Color color_;
  float ambient_;
  float diffuse_;
  float specular_;
  float shininess_;
};
