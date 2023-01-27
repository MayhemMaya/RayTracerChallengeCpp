#pragma once

#include <iostream>
#include "color.h"
#include "utils.h"
#include "pattern.h"

class Material {
 public:
   Material();
   Material(const Color& color, float ambient, float diffuse,
            float specular, float shininess, Pattern* pattern);
   ~Material();
   Color GetColor() const;
   float GetAmbient() const;
   float GetDiffuse() const;
   float GetSpecular() const;
   float GetShininess() const;
   Pattern* GetPattern() const;

   void SetColor(const Color& color);
   void SetAmbient(float ambient);
   void SetDiffuse(float diffuse);
   void SetSpecular(float specular);
   void SetShininess(float shininess);
   void SetPattern(Pattern* pattern);
   bool operator==(const Material& other) const;
   Material& operator=(const Material& other);
   std::string format() const;
 private:
  Color color_;
  float ambient_;
  float diffuse_;
  float specular_;
  float shininess_;
  Pattern* pattern_;
};
