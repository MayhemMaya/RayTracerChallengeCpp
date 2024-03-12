#include "materials.h"

Material Materials::Default = Material();

Material Materials::TransparentYellow = Material(
  Colors::Yellow, // color
  0.2f,           // ambient
  0.0f,           // diffuse
  0.0f,           // specular
  0.0f,           // shininess
  0.0f,           // reflectivity
  0.8f,           // transparency
  1.0f            // refractive_index
);