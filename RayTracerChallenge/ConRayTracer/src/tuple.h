#ifndef TUPLE_H
#define TUPLE_H

#include <iostream>

class Tuple {
 public:
  Tuple(float x, float y, float z, float w);
  virtual ~Tuple();
  friend std::ostream& operator<<(std::ostream& os, const Tuple& obj);
  float operator [] (unsigned int index) const;
  virtual bool operator == (const Tuple& other) const;
  bool IsPoint() const;
  bool IsVector() const;
  Tuple operator+(const Tuple& other) const;
  virtual Tuple operator - (const Tuple& other) const;
  Tuple operator - () const;
  Tuple operator * (const float& scalar) const;
  Tuple operator / (const float& scalar) const;
 protected:
  float x_, y_, z_, w_;
};

#endif // TUPLE_H
