#pragma once

#include "mesh.h"

class Sphere : public Mesh {
 public:
   Sphere();
   Sphere(std::string name);
   Sphere(Material material);
   Sphere(Matrix4 transform);
   Sphere(std::string name, Material material);
   Sphere(std::string name, Matrix4 transform);
   Sphere(Material material, Matrix4 transform);
   Sphere(std::string name, Material material, Matrix4 transform);
   bool operator==(const Object& object) const override;
   Sphere& operator=(const Object& other) override;
};
