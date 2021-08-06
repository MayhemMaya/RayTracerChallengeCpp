#pragma once

#include <iostream>
#include "matrix4.h"
#include "point.h"

class Object {
 public:
   Object(std::string name);
   Object(std::string name, const Point& position);
   virtual ~Object() = 0;
   std::string GetName() const;
   void SetName(const std::string& name);
   Matrix4 GetTransform() const;
   void SetTransform(const Matrix4& transform);
   Point GetPosition() const;
   bool operator==(const Object& other) const;
   static int GetCount();

 private:
   static int object_count_;
   std::string name_;
   Matrix4 transform_;
};
