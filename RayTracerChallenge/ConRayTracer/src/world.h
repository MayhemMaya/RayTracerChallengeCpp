#pragma once

#include <vector>
#include "object.h"
#include "light-source.h"
#include "shape.h"
#include "point-light.h"
#include "sphere.h"
#include "Camera.h"

enum class WorldType {
  EMPTY,
  DEFAULT
};

class World {
 public:
   World();
   World(const WorldType& type);
   ~World();
   std::vector<Object*> GetObjects() const;
   std::vector<LightSource*> GetLights() const;
   std::vector<Shape*> GetShapes() const;
   std::vector<Camera*> GetCameras() const;
   int GetObjectCount() const;
   void ListObjects() const;
   void ListObjects(const ObjectType& type) const;
   void AddObject(Object* other);
   void DeleteObject(const std::string& name);
   bool ContainsLightSource() const;
   bool ContainsCamera() const;
   bool ContainsObject(Object* other) const;
 private:
   std::vector<Object*> objects_;
   bool hasLightSource_;
};
