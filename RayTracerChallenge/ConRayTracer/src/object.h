#pragma once

#include <iostream>
#include "matrix4.h"
#include "point.h"
#include "utils.h"
#include <string>
#include <map>

static enum class ObjectType {
  kUnknown,
  kShape,
  kSphere,
  kPointLight,
  kCamera,
  kPlane, 
  kCube,
  kCylinder,
  kCone,
  kGroup
};

static std::map<ObjectType, std::string> typeMap {
  {ObjectType::kUnknown, "kUnknown"},
  {ObjectType::kShape, "kShape"},
  {ObjectType::kSphere, "kSphere"},
  {ObjectType::kPointLight, "kPointLight"},
  {ObjectType::kCamera, "kCamera"},
  {ObjectType::kPlane, "kPlane"},
  {ObjectType::kCube, "kCube"},
  {ObjectType::kCylinder, "kCube"},
  {ObjectType::kCone, "kCone"},
  {ObjectType::kGroup, "kGroup"},
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
   Object* GetParent() const;
   void SetParent(Object* parent);
   void RemoveParent();
   bool HasParent() const;
   void SetObjectType(const ObjectType& type);
   virtual Point GetPosition() const;
   virtual bool operator==(const Object& other);
   virtual Object& operator=(const Object& other);
   static int GetCount();
   static Point world_to_object(const Object* shape, Point point);

 protected:
   static int object_count_;
   std::string name_;
   ObjectType type_;
   Matrix4 transform_;
   Object* parent_;
};
