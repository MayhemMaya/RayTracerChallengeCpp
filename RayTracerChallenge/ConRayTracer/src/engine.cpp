#include "engine.h"

namespace Engine {

Color lighting(const Material& material, Shape* object,
                                         const LightSource& light,
                                         const Point& point,
                                         const Vector& eyev,
                                         const Vector& normalv,
                                         bool in_shadow) {
  Color color;
  
  // check if the material has a pattern, if it does set the color to the pattern's color at the given point
  if (material.GetPattern() != nullptr) {
    Pattern* pattern = material.GetPattern();
    color = pattern->pattern_at_object(object, point);
  }
  else {
    // otherwise set it to the color of the material
    color = material.GetColor();
  }

  // Now compute the light as usual
  // set diffuse and specular to black to start
  Color diffuse(0, 0, 0);
  Color specular(0, 0, 0);

  // combine the surface color with the light's color/intensity
  Color effective_color = color * light.GetIntensity();

  // find the direction to the light source
  Vector lightv = (light.GetPosition() - point).normalize();

  // compute the ambient contribution
  Color ambient = effective_color * material.GetAmbient();
  if (in_shadow) return ambient + diffuse + specular;

  // light_dot_normal represents the cosine of the angle between the
  // light vector and the normal vector. A negative number means the
  // light is on the other side of the surface.
  float light_dot_normal = lightv.dot(normalv);
  if (light_dot_normal < 0) {
    diffuse = Color(0, 0, 0); // black
    specular = Color(0, 0, 0); // black
  }
  else {
    // compute the diffuse contribution
    diffuse = effective_color * material.GetDiffuse() * light_dot_normal;

    // reflect_dot_eye represents the cosine of the angle between the
    // reflection vector and the eye vector. A negative number means the
    // light reflects away from the eye.
    Vector reflectv = -lightv.reflect(normalv);
    float reflect_dot_eye = reflectv.dot(eyev);

    if (reflect_dot_eye <= 0) {
      specular = Color(0, 0, 0); // black
    }
    else {
      // compute the specular contribution
      float factor = pow(reflect_dot_eye, material.GetShininess());
      specular = light.GetIntensity() * material.GetSpecular() * factor;
    }
  }
  return ambient + diffuse + specular;
}

bool contains_intersection_object(const std::vector<Object*>& containers_list, Object* obj) {
  for (auto& item : containers_list) {
    if ((*item) == (*obj)) {
      return true;
    }
  }
  return false;
}

void remove_intersection_object(std::vector<Object*>& containers_list, Object* obj) {
  for (int i = 0; i < containers_list.size(); i++) {
    if ((*containers_list[i]) == (*obj)) {
      containers_list.erase(containers_list.begin() + i);
    }
  }
}

float calculate_n_value(const std::vector<Object*> containers_list) {
  // check if containers is not empty
  if (containers_list.size() != 0) {
    // get the last object in the containers array
    Shape* last_obj = (Shape*)containers_list.at(containers_list.size() - 1);
    // then return it's refractive index
    return last_obj->GetMaterial().GetRefractiveIndex();
  }
  // if containers is empty return a refractive index of 1.0f
  return 1.0f;
}

Computation prepare_computations(const Intersection& intersection, const Ray& ray) {
  // this function is an overload which calls the other prepare_computations(const Intersection& intersection, const Ray& ray, const std::vector<Intersection>& intersections)
  // function since we cannot set the intersections array in that function to a default array value containing a single element
  // which is the single intersection parameter (the first argument of that function).
  Computation comps = prepare_computations(intersection, ray, { intersection });
  return comps;
}

Computation prepare_computations(const Intersection& intersection, const Ray& ray, const std::vector<Intersection>& intersections) {
  Point comps_point = ray.position(intersection.GetTime());
  Shape* intersection_object = (Shape*)intersection.GetObject();
  Vector comps_normalv = intersection_object->normal_at(comps_point);
  Computation comps = Computation(
    intersection.GetTime(),                           // comps.time
    intersection_object,                              // comps.object
    comps_point,                                      // comps.point
    -ray.GetDirection(),                              // comps.eyev
    comps_normalv,                                    // comps.normalv
    ray.GetDirection().reflect(comps_normalv)         // comps.reflectv
  );

  std::vector<Object*> containers;

  for (auto& _intersection : intersections) {
    // check if the intersection is the hit
    if (_intersection == intersection) {
      comps.n1 = calculate_n_value(containers);
    }

    Object* intersection_object = _intersection.GetObject();

    if (contains_intersection_object(containers, intersection_object)) {
      // remove the intersection object
      remove_intersection_object(containers, intersection_object);
    }
    else {
      // otherwise add it to the containers array
      containers.push_back(intersection_object);
    }

    // check if the intersection is the hit again
    if (_intersection == intersection) {
      comps.n2 = calculate_n_value(containers);
      break;
    }
  }
  
  if (comps.normalv.dot(comps.eyev) < 0) {
    comps.inside = true;
    comps.normalv = -comps.normalv;
  }
  else comps.inside = false;
  
  comps.over_point = comps.point + comps.normalv * utils::kEPSILON;

  comps.under_point = comps.point - comps.normalv * utils::kEPSILON;

  return comps;
}

Color shade_hit(const World& world, const Computation& comps, int recursive_calls_remaining) {

  if (!utils::kUSE_ALL_LIGHTS) {
    bool shadowed = is_shadowed(world, comps.over_point);
    Color surface = lighting(comps.object->GetMaterial(), comps.object, (*world.GetLights()[0]),
                                   comps.over_point, comps.eyev, comps.normalv, shadowed);
    Color reflected = reflected_color(world, comps, recursive_calls_remaining);
    Color refracted = refracted_color(world, comps, recursive_calls_remaining);

    if (comps.object->GetMaterial().GetReflectivity() > 0 &&
        comps.object->GetMaterial().GetTransparency() > 0) {
      float reflectance = schlick(comps);
      return surface + reflected * reflectance + refracted * (1 - reflectance);
    }

    return surface + reflected + refracted;
  }
  
  Color hit_color;
  
  for (auto light : world.GetLights()) {
    bool shadowed = is_shadowed(world, comps.over_point);
    Color surface = lighting(comps.object->GetMaterial(), comps.object, (*light),
      comps.over_point, comps.eyev, comps.normalv, shadowed);
    Color reflected = reflected_color(world, comps, recursive_calls_remaining);
    Color refracted = refracted_color(world, comps, recursive_calls_remaining);

    if (comps.object->GetMaterial().GetReflectivity() > 0 &&
      comps.object->GetMaterial().GetTransparency() > 0) {
      float reflectance = schlick(comps);
      return surface + reflected * reflectance + refracted * (1 - reflectance);
    }
    hit_color += surface + reflected + refracted;
  }
  return hit_color;
}

Color color_at(const World& world, const Ray& ray, int recursive_calls_remaining) {
  std::vector<Intersection> xs = ray.intersect(world);
  Hit hit = Hit::hit(xs);
  
  if (hit.result == HitResult::HIT) {
    Intersection i = hit.i;
    Engine::Computation comps = Engine::prepare_computations(i, ray, xs);
    Color c = Engine::shade_hit(world, comps, recursive_calls_remaining);
    return c;
  }
  
  return Color(0.0f, 0.0f, 0.0f);
}

Ray ray_for_pixel(const Camera& camera, int px, int py) {
  // the offset from the edge of the canvas to the pixel's center
  float xoffset = (px + 0.5f) * camera.GetPixelSize();
  float yoffset = (py + 0.5f) * camera.GetPixelSize();

  // the untransformed coordinates of the pixel in world space.
  // (remember that the camera looks toward -z, so +x is to the *left*.)
  float world_x = camera.GetHalfWidth() - xoffset;
  float world_y = camera.GetHalfHeight() - yoffset;

  // using the camera matrix, transform the canvas point and the origin,
  // and then compute the ray's direction vector.
  // (remember that the canvas is at z=-1)
  Point pixel = camera.GetSavedTransformInverse() * Point(world_x, world_y, -1.0f);
  Point origin = camera.GetSavedTransformInverse() * Point(0, 0, 0);
  Vector direction = (pixel - origin).normalize();
  return Ray(origin, direction);
}

Canvas render(const Camera& camera, const World& world) {
  int pixel_count = camera.GetHorizontalSize() * camera.GetVerticalSize();
  int pixel_position = 0;

  Canvas image(camera.GetHorizontalSize(), camera.GetVerticalSize());

  for (int y = 0; y < camera.GetVerticalSize(); y++) {
    for (int x = 0; x < camera.GetHorizontalSize(); x++) {
      Ray ray = ray_for_pixel(camera, x, y);
      Color color = color_at(world, ray);
      image.WritePixel(x, y, color);
      float progress = utils::roundoff(utils::map(pixel_position, 0, pixel_count, 0.0f, 1.0f), 2);
      int progress_int = int(progress * 100.0);
      std::cout << "Rendering in progress... " << progress_int << "% complete." << std::endl;
      pixel_position++;
    }
  }
  std::cout << std::endl;

  return image;
}

bool is_shadowed(const World& world, const Point& point) {
  /*
  * This was not mentioned in the book but if multiple light sources are present in the world
  * we must iterate through each light and calculate wether the point is lit by at least one of them.
  * If the point is not lit by at least one of them it is in shadow and we can return true, if not we return false.
  */
  // ^^^ IGNORE THIS ^^^

  Vector v = world.GetLights()[0]->GetPosition() - point;
  double distance = v.magnitude();
  Vector direction = v.normalize();
  Ray r(point, direction);

  std::vector<Intersection> xs = r.intersect(world);

  Hit hit = Hit::hit(xs);

  if (hit.result == HitResult::HIT && hit.i.GetTime() < distance) {
    return true;
  }
  return false;

  //std::vector<bool> shadowed_hits;
  //
  //for (auto light : world.GetLights()) {
  //  Vector v = light->GetPosition() - point;
  //  float distance = v.magnitude();
  //  Vector direction = v.normalize();
  //  Ray r(point, direction);

  //  std::vector<Intersection> xs = r.intersect(world);

  //  Hit hit = Hit::hit(xs);

  //  if (hit.result == HitResult::HIT &&
  //    hit.i.GetTime() < distance) {
  //    shadowed_hits.push_back(true);
  //  }
  //  else {
  //    shadowed_hits.push_back(false);
  //  }
  //}

  //// check if at least one hit was shadowed
  //bool shadowed_hit = utils::at_least_one_true(shadowed_hits);
  //return shadowed_hit;
}

Color reflected_color(const World& world, const Computation& comps, int recursive_calls_remaining) {
  if (comps.object->GetMaterial().GetReflectivity() == 0 ||
      recursive_calls_remaining < 1) {
    return Color(0, 0, 0);
  }
  Ray reflect_ray = Ray(comps.over_point, comps.reflectv);
  Color color = color_at(world, reflect_ray, recursive_calls_remaining -= 1);
  return color * comps.object->GetMaterial().GetReflectivity();
}

Color refracted_color(const World& world, const Computation& comps, int recursive_calls_remaining) {
  // Get the object transparency
  float object_transarency = comps.object->GetMaterial().GetTransparency();

  // Find the ratio of first index of refraction to the second.
  // (Yup, this is inverted from the definition of Snell's Law.)
  float n_ratio = comps.n1 / comps.n2;

  // cos(theta_i) is the same as the dot product of the two vectors
  float cos_i = comps.eyev.dot(comps.normalv);

  // Find sin(theta_t)^2 via trigonometric identity
  float sin2_t = pow(n_ratio, 2) * (1 - pow(cos_i, 2));

  if (object_transarency == 0 ||
      recursive_calls_remaining < 1 ||
      sin2_t > 1) { // check if the 'sin2_t' value is greater than 1 to check for total internal reflection
    return Color(0, 0, 0);
  }

  // Find cos(theta_t) via trigonometric identity
  float cos_t = sqrt(1.0 - sin2_t);

  // Compute the direction of the refracted ray
  Vector direction = comps.normalv * (n_ratio * cos_i - cos_t) - comps.eyev * n_ratio;

  // Create the refracted ray
  Ray refract_ray = Ray(comps.under_point, direction);

  // Find the color of the refracted ray, making sure to multiply
  // by the transparency value to account for any opacity
  Color color = color_at(world, refract_ray, recursive_calls_remaining - 1) * object_transarency;

  return color.round(4);
}

float schlick(const Computation& comps) {
  // find the cosine of the angle between the eye and normal vectors
  double cos = comps.eyev.dot(comps.normalv);

  // total internal reflection can only occur if n1 > n2
  if (comps.n1 > comps.n2) {
    double n = comps.n1 / comps.n2;
    double sin2_t = pow(n, 2) * (1.0f - pow(cos, 2));

    if (sin2_t > 1.0f) {
      return 1.0f;
    }

    // compute cosine of theta_t using trig identity
    double cos_t = sqrt(1.0f - sin2_t);

    // when n1 > n2, use cos(theta_t) instead
    cos = cos_t;
  }

  double r0 = pow(((comps.n1 - comps.n2) / (comps.n1 + comps.n2)), 2);
  return r0 + (1 - r0) * pow((1 - cos), 5);
}

} // namespace Engine