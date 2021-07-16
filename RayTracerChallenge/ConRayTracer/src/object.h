#pragma once

#include <iostream>
#include "matrix4.h"
#include "point.h"

class Object {
 public:
   Object();
   Object(std::string name);
   friend std::ostream& operator<<(std::ostream& os, const Object& obj);
   std::string GetName() const;
   Matrix4 GetTransform() const;
   void SetTransform(const Matrix4& transform);
   Point GetPosition() const;
   bool operator==(const Object& other) const;

 private:
   static int object_count_;
   std::string name_;
   Matrix4 transform_;
};
