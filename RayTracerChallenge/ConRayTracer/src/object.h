#pragma once

#include <iostream>
#include "matrix4.h"
#include "point.h"
#include "utils.h"
#include <string>
#include <atomic>
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
  kGroup,
  kTriangle
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
  {ObjectType::kTriangle, "kTriangle"},
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
   Matrix4 GetCachedTransformInverse() const;
   virtual void SetTransform(const Matrix4& transform);
   ObjectType GetObjectType() const;
   std::string GetObjectTypeName() const;
   Object* GetParent() const;
   void SetParent(Object* parent);
   void RemoveParent();
   bool HasParent() const;
   void SetObjectType(const ObjectType& type);
   Point GetPosition() const;
   virtual bool operator==(const Object& other) const;
   bool compareWithoutID(const Object& other) const;
   virtual Object& operator=(const Object& other);
   static Point world_to_object(const Object* shape, Point point);
   uint64_t GetID() const;
private:
   static std::atomic<uint64_t> ID;

 protected:
   std::string name_;
   uint64_t id_;
   ObjectType type_;
   Matrix4 transform_;
   Matrix4 cached_transform_inverse_;
   Object* parent_;
};
