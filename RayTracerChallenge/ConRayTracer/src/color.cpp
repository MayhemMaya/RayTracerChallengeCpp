
#include "color.h"
#include "utils.h"

Color::Color() : r_(0), g_(0), b_(0) {}
Color::Color(float r, float g, float b)
    : r_(r), g_(g), b_(b) {}

std::ostream& operator<<(std::ostream& os, const Color& obj) {
  os << "(" << obj.r_ << ", " << obj.g_ << ", " << obj.b_ << ")";
  return os;
}

std::string Color::ToPPMString() const {
  std::stringstream ss;
  ss << utils::clamp(std::round(r_ * 255), 0, 255) << " "
     << utils::clamp(std::round(g_ * 255), 0, 255) << " "
     << utils::clamp(std::round(b_ * 255), 0, 255);
  return ss.str();
}

float Color::operator[](unsigned int index) const {
  switch (index) {
  case 0: return r_;
  case 1: return g_;
  case 2: return b_;
  }
}

bool Color::operator==(const Color& other) const {
  return(utils::equal(r_, other[0]) && utils::equal(g_, other[1]) &&
                                       utils::equal(b_, other[2]));
}

Color Color::operator+(const Color& other) const {
  return Color(r_ + other[0], g_ + other[1], b_ + other[2]);
}

Color Color::operator-(const Color& other) const {
  return Color(r_ - other[0], g_ - other[1], b_ - other[2]);
}

Color Color::operator*(float scalar) const {
  return Color(r_ * scalar, g_ * scalar, b_ * scalar);
}

Color Color::operator*(const Color& other) const {
  return Color(this->hadamard_product(other));
}

Color Color::operator/(float value) const {
  return Color(r_ / value, g_ / value, b_ / value);
}

Color& Color::operator+=(const Color& other) {
  this->r_ += other[0];
  this->g_ += other[1];
  this->b_ += other[2];
  return *this;
}

Color Color::clamp() const {
  return Color(utils::clamp(r_, 0.0, 1.0), utils::clamp(g_, 0.0f, 1.0f),
                                           utils::clamp(b_, 0.0f, 1.0f));
}

Color Color::round(int roundoff_amount) const {
  return Color(utils::roundoff(r_, roundoff_amount),
               utils::roundoff(g_, roundoff_amount),
               utils::roundoff(b_, roundoff_amount));
}

Color Color::hadamard_product(const Color& other) const {
  return Color((*this)[0] * other[0], (*this)[1] * other[1], (*this)[2] * other[2]);
}