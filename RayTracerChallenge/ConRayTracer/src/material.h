#pragma once

#include <iostream>
#include "color.h"
#include "utils.h"

class Material {
 public:
   Material();
   Material(const Color& color, float ambient, float diffuse,
            float specular, float shininess);
   friend std::ostream& operator<<(std::ostream& os, const Material& obj);
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
   Material& operator=(const Material& other);
   std::string format() const;
 private:
  Color color_;
  float ambient_;
  float diffuse_;
  float specular_;
  float shininess_;
};
