#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H


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

#endif // ENVIRONMENT_H
