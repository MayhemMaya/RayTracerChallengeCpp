#pragma once


#include "vector.h"

class Environment {
 public:
   Environment(Vector gravity, Vector wind);
   Vector GetGravity() const;
   Vector GetWind() const;
 private:
   Vector gravity_;
   Vector wind_;
};
