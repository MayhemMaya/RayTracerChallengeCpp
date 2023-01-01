#pragma once

#include <iostream>

class Tuple {
 public:
  Tuple();
  Tuple(float x, float y, float z, float w);
  virtual ~Tuple() = 0;
  float operator [] (int index) const;
  void operator()(int index, float value);
  bool IsPoint() const;
  bool IsVector() const;
  virtual bool operator == (const Tuple& other) const = 0;
 protected:
  float x_, y_, z_, w_;
};
