#pragma once

#include "utils.h"

class Color {
 public:
   Color();
   Color(float r, float g, float b);
   friend std::ostream& operator<<(std::ostream& os, const Color& obj);
   std::string ToPPMString() const;
   float operator[](unsigned int index) const;
   bool operator==(const Color& other) const;
   Color operator+(const Color& other) const;
   Color operator-(const Color& other) const;
   Color operator*(float scalar) const;
   Color operator*(const Color& other) const;
   Color operator/(float value) const;
   Color& operator+=(const Color& other);
   Color clamp() const;
   Color round(int roundoff_amount) const;
   Color hadamard_product(const Color& other) const;

 private:
  float r_, g_, b_;
};
