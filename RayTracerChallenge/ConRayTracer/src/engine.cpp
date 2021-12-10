#include "engine.h"

namespace Engine {

Color lighting(const Material& material, const LightSource& light,
                                         const Point& point,
                                         const Vector& eyev,
                                         const Vector& normalv) {
  // set diffuse and specular to black to start
  Color diffuse(0, 0, 0);
  Color specular(0, 0, 0);

  // combine the surface color with the light's color/intensity
  Color effective_color = material.GetColor() * light.GetIntensity();

  // find the direction to the light source
  Vector lightv = (light.GetPosition() - point).normalize();

  // compute the ambient contribution
  Color ambient = effective_color * material.GetAmbient();

  // light_dot_normal represents the cosine of the angle between the
  // light vector and the normal vector. A negative number means the
  // light is on the other side of the surface.
  float light_dot_normal = utils::dot(lightv, normalv);
  if (light_dot_normal < 0) {
    diffuse = Color(0, 0, 0); // black
    specular = Color(0, 0, 0); // black
  }
  else {
    // compute the diffuse contribution
    diffuse = effective_color * material.GetDiffuse() * light_dot_normal;

    // reflect_dot_eye represents the cosine of the angle between the
    // reflection vectorand the eye vector.A negative number means the
    // light reflects away from the eye.
    Vector reflectv = -lightv.reflect(normalv);
    float reflect_dot_eye = utils::dot(reflectv, eyev);

    if (reflect_dot_eye <= 0) {
      specular = Color(0, 0, 0); // black
    }
    else {
      // compute the specular contribution
      float factor = pow(reflect_dot_eye, material.GetShininess());
      specular = light.GetIntensity() * material.GetSpecular() * factor;
    }
  }
  return(ambient + diffuse + specular);
}

Computation prepare_computations(const Intersection& intersection, const Ray& ray) {
  Computation comps;

  comps.time_ = intersection.GetTime(); // comps.time
  comps.object_ = intersection.GetObject(); // comps.object
  comps.point_ = ray.position(intersection.GetTime()); // comps.point
  comps.eyev_ = -ray.GetDirection(); // comps.eyev
  comps.normalv_ = intersection.GetObject().normal_at(comps.point_); // comps.normalv
  
  if (utils::dot(comps.normalv_, comps.eyev_) < 0) {
    comps.inside_ = true;
    comps.normalv_ = -comps.normalv_;
  }
  else comps.inside_ = false;
  
  return comps;
  }

Color shade_hit(const World& world, const Computation& comps) {
  Color hit_color;
  for (auto light : world.GetLights()) {
    hit_color += lighting(comps.object_.GetMaterial(), (*light),
                         comps.point_, comps.eyev_, comps.normalv_);
  }
  return hit_color;
}

Color color_at(const World& world, const Ray& ray) {
  std::vector<Intersection> xs = ray.intersect(world);
  Hit hit = Hit::hit(xs);
  
  if (hit.result == HitResult::HIT) {
    Intersection i = hit.i;
    Engine::Computation comps = Engine::prepare_computations(i, ray);
    Color c = Engine::shade_hit(world, comps);
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
  Point pixel = camera.GetTransform().inverse() * Point(world_x, world_y, -1.0f);
  Point origin = camera.GetTransform().inverse() * Point(0, 0, 0);
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
      utils::ClearScreen();
      float progress = utils::roundoff(utils::map(pixel_position, 0, pixel_count, 0.0f, 1.0f), 2);
      std::cout << "Rendering in progress... " << int(progress * 100.0) << "% complete." << std::endl;
      pixel_position++;
    }
  }
  std::cout << std::endl;
  return image;
}

} // namespace Engine