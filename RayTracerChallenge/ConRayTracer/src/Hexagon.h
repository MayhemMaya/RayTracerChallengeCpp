#pragma once

#include <string>
#include <array>
#include "group.h"
#include "material.h"
#include "sphere.h"
#include "cylinder.h"

class Hexagon : public Group {
public:
  Hexagon(const std::string& name, const Material& material);
private:
  std::array<Sphere, 6> corners_;
  std::array<Cylinder, 6> edges_;
  std::array<Group, 6> sides_;
};