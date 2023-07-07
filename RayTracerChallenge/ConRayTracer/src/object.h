#pragma once

#include <iostream>
#include "matrix4.h"
#include "point.h"
#include "utils.h"
#include <string>

enum class ObjectType {
  kUnknown,
  kShape,
  kSphere,
  kPointLight,
  kCamera,
  kPlane, 
  kCube
};

static std::string type_names[] = {
  "unknown",
  "shape",
  "sphere",
  "pointLight",
  "camera",
  "plane"
  "glass_sphere"
};

class Object {
 public:
   Object(const std::string& name, const ObjectType& type);
   Object(const std::string& name, const ObjectType& type, const Matrix4& transform);
   Object(const std::string& name, const ObjectType& type, const Point& position);
   virtual ~Object() = 0;
   virtual void ListDetails();
   std::string GetName() const;
   void SetName(const std::string& name);
   Matrix4 GetTransform() const;
   void SetTransform(const Matrix4& transform);
   ObjectType GetObjectType() const;
   std::string GetObjectTypeName() const;
   void SetObjectType(const ObjectType& type);
   Matrix4 GetSavedTransformInverse() const;
   virtual Point GetPosition() const;
   virtual bool operator==(const Object& other);
   virtual Object& operator=(const Object& other);
   static int GetCount();
 protected:
   static int object_count_;
   std::string name_;
   ObjectType type_;
   Matrix4 transform_;
   Matrix4 saved_transform_inverse_;
};
