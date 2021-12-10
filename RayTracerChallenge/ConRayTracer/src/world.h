#pragma once

#include <vector>
#include "object.h"
#include "light-source.h"
#include "mesh.h"
#include "point-light.h"
#include "sphere.h"
#include "Camera.h"

enum class WorldType {
  EMPTY,
  DEFAULT
};

class World {
 public:
   World() = default;
   World(const WorldType& type);
   ~World();
   std::vector<Object*> GetObjects() const;
   std::vector<LightSource*> GetLights() const;
   std::vector<Mesh*> GetMeshes() const;
   std::vector<Camera*> GetCameras() const;
   int GetObjectCount() const;
   void ListObjects() const;
   void ListObjects(ObjectType type) const;
   void AddObject(Object* object);
   void DeleteObject(std::string name);
   bool ContainsLightSource() const;
   bool ContainsCamera() const;
   bool ContainsObject(Object* object) const;
 private:
   std::vector<Object*> objects_;
};
