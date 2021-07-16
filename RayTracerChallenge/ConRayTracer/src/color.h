#pragma once

#include <iostream>
#include <string>

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
   Color operator*(const float& scalar) const;
   Color operator*(const Color& other) const;
   Color clamp() const;

 private:
  float r_, g_, b_;
};
