#pragma once

#include <iostream>
#include "matrix4.h"
#include "point.h"
#include "utils.h"

enum class ObjectType {
  kUnknown,
  kMesh,
  kSphere,
  kPointLight,
  kCamera
};

static std::string type_enum_names[] = {
  "kUnknown",
  "kMesh",
  "kSphere",
  "kPointLight",
  "kCamera"
};

class Object {
 public:
   Object(const std::string& name, const ObjectType& type);
   Object(const std::string& name, const ObjectType& type, const Matrix4& transform);
   Object(const std::string& name, const ObjectType& type, const Point& position);
   virtual ~Object() = 0;
   virtual void ListDetails() const;
   std::string GetName() const;
   void SetName(const std::string& name);
   Matrix4 GetTransform() const;
   void SetTransform(const Matrix4& transform);
   ObjectType GetObjectType() const;
   std::string GetObjectTypeName() const;
   void SetObjectType(const ObjectType& type);
   virtual Point GetPosition() const;
   virtual bool operator==(const Object& other) const;
   virtual Object& operator=(const Object& other);
   static int GetCount();
 protected:
   static int object_count_;
   std::string name_;
   ObjectType type_;
   Matrix4 transform_;
};
